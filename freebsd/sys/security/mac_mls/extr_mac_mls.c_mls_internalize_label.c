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
struct mac_mls {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_MLS_LABEL_NAME ; 
 struct mac_mls* SLOT (struct label*) ; 
 int mls_parse (struct mac_mls*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
mls_internalize_label(struct label *label, char *element_name,
    char *element_data, int *claimed)
{
	struct mac_mls *mm, mm_temp;
	int error;

	if (strcmp(MAC_MLS_LABEL_NAME, element_name) != 0)
		return (0);

	(*claimed)++;

	error = mls_parse(&mm_temp, element_data);
	if (error)
		return (error);

	mm = SLOT(label);
	*mm = mm_temp;

	return (0);
}