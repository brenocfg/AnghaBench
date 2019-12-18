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
struct usb_filt {int dummy; } ;
struct bpf_program {struct usb_filt* bf_insns; } ;

/* Variables and functions */
 struct usb_filt* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct usb_filt*) ; 
 int /*<<< orphan*/  usb_filt_head ; 

__attribute__((used)) static void
free_filter(struct bpf_program *pprog)
{
	struct usb_filt *puf;

	while ((puf = STAILQ_FIRST(&usb_filt_head)) != NULL) {
		STAILQ_REMOVE_HEAD(&usb_filt_head, entry);
		free(puf);
	}
	free(pprog->bf_insns);
}