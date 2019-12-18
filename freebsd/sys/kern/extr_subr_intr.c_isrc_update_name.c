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
struct intr_irqsrc {char* isrc_name; scalar_t__ isrc_index; } ;

/* Variables and functions */
 int INTRNAME_LEN ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  intrcnt_setname (char*,scalar_t__) ; 
 int /*<<< orphan*/  isrc_table_lock ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 

__attribute__((used)) static void
isrc_update_name(struct intr_irqsrc *isrc, const char *name)
{
	char str[INTRNAME_LEN];

	mtx_assert(&isrc_table_lock, MA_OWNED);

	if (name != NULL) {
		snprintf(str, INTRNAME_LEN, "%s: %s", isrc->isrc_name, name);
		intrcnt_setname(str, isrc->isrc_index);
		snprintf(str, INTRNAME_LEN, "stray %s: %s", isrc->isrc_name,
		    name);
		intrcnt_setname(str, isrc->isrc_index + 1);
	} else {
		snprintf(str, INTRNAME_LEN, "%s:", isrc->isrc_name);
		intrcnt_setname(str, isrc->isrc_index);
		snprintf(str, INTRNAME_LEN, "stray %s:", isrc->isrc_name);
		intrcnt_setname(str, isrc->isrc_index + 1);
	}
}