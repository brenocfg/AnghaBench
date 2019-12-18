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
struct hws_trailer_entry {int /*<<< orphan*/  f; } ;
struct hws_basic_entry {int /*<<< orphan*/  def; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_sprintf_event (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hws_basic_entry*) ; 
 int /*<<< orphan*/  sfdbg ; 

__attribute__((used)) static void debug_sample_entry(struct hws_basic_entry *sample,
			       struct hws_trailer_entry *te)
{
	debug_sprintf_event(sfdbg, 4, "hw_collect_samples: Found unknown "
			    "sampling data entry: te->f=%i basic.def=%04x "
			    "(%p)\n",
			    te->f, sample->def, sample);
}