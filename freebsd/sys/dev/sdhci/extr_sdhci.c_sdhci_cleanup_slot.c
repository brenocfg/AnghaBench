#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sdhci_slot {int opt; int /*<<< orphan*/  tune_data; int /*<<< orphan*/  tune_cmd; int /*<<< orphan*/  tune_req; int /*<<< orphan*/  bus; int /*<<< orphan*/ * dev; int /*<<< orphan*/  card_delayed_task; int /*<<< orphan*/  card_task; int /*<<< orphan*/  retune_callout; int /*<<< orphan*/  card_poll_callout; int /*<<< orphan*/  timeout_callout; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int SDHCI_HAVE_DMA ; 
 int /*<<< orphan*/  SDHCI_LOCK (struct sdhci_slot*) ; 
 int /*<<< orphan*/  SDHCI_LOCK_DESTROY (struct sdhci_slot*) ; 
 int /*<<< orphan*/  SDHCI_RESET_ALL ; 
 int SDHCI_TUNING_SUPPORTED ; 
 int /*<<< orphan*/  SDHCI_UNLOCK (struct sdhci_slot*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_dma_free (struct sdhci_slot*) ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi_giant ; 

int
sdhci_cleanup_slot(struct sdhci_slot *slot)
{
	device_t d;

	callout_drain(&slot->timeout_callout);
	callout_drain(&slot->card_poll_callout);
	callout_drain(&slot->retune_callout);
	taskqueue_drain(taskqueue_swi_giant, &slot->card_task);
	taskqueue_drain_timeout(taskqueue_swi_giant, &slot->card_delayed_task);

	SDHCI_LOCK(slot);
	d = slot->dev;
	slot->dev = NULL;
	SDHCI_UNLOCK(slot);
	if (d != NULL)
		device_delete_child(slot->bus, d);

	SDHCI_LOCK(slot);
	sdhci_reset(slot, SDHCI_RESET_ALL);
	SDHCI_UNLOCK(slot);
	if (slot->opt & SDHCI_HAVE_DMA)
		sdhci_dma_free(slot);
	if (slot->opt & SDHCI_TUNING_SUPPORTED) {
		free(slot->tune_req, M_DEVBUF);
		free(slot->tune_cmd, M_DEVBUF);
		free(slot->tune_data, M_DEVBUF);
	}

	SDHCI_LOCK_DESTROY(slot);

	return (0);
}