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
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PARTITION_LABEL_NAME ; 
 int /*<<< orphan*/  SLOT_SET (struct label*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
partition_cred_internalize_label(struct label *label, char *element_name,
    char *element_data, int *claimed)
{

	if (strcmp(MAC_PARTITION_LABEL_NAME, element_name) != 0)
		return (0);

	(*claimed)++;
	SLOT_SET(label, strtol(element_data, NULL, 10));
	return (0);
}