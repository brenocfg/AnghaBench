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
struct payload_list {int dummy; } ;
struct dst_list {struct dst_list* dl_next; } ;

/* Variables and functions */
 struct dst_list* dl_head ; 
 int /*<<< orphan*/  rrenum_output (struct payload_list*,struct dst_list*) ; 

__attribute__((used)) static void
rrenum_snd_eachdst(struct payload_list *pl)
{
	struct dst_list *dl;

	for (dl = dl_head; dl; dl = dl->dl_next) {
		rrenum_output(pl, dl);
	}
}