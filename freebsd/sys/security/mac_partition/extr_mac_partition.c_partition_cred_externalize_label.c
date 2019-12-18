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
struct sbuf {int dummy; } ;
struct label {int dummy; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAC_PARTITION_LABEL_NAME ; 
 scalar_t__ SLOT (struct label*) ; 
 int sbuf_printf (struct sbuf*,char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
partition_cred_externalize_label(struct label *label, char *element_name,
    struct sbuf *sb, int *claimed)
{

	if (strcmp(MAC_PARTITION_LABEL_NAME, element_name) != 0)
		return (0);

	(*claimed)++;

	if (label != NULL) {
		if (sbuf_printf(sb, "%jd", (intmax_t)SLOT(label)) == -1)
			return (EINVAL);
	} else {
		if (sbuf_printf(sb, "0") == -1)
			return (EINVAL);
	}
	return (0);
}