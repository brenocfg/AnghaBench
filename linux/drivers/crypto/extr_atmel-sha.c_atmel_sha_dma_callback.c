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
struct atmel_sha_dev {int is_async; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA_IER ; 
 int /*<<< orphan*/  SHA_INT_DATARDY ; 
 int /*<<< orphan*/  atmel_sha_write (struct atmel_sha_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_sha_dma_callback(void *data)
{
	struct atmel_sha_dev *dd = data;

	dd->is_async = true;

	/* dma_lch_in - completed - wait DATRDY */
	atmel_sha_write(dd, SHA_IER, SHA_INT_DATARDY);
}