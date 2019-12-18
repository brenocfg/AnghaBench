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

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_CHECK (struct label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_IFNET ; 
 int /*<<< orphan*/  ifnet_externalize_label ; 

__attribute__((used)) static int
test_ifnet_externalize_label(struct label *label, char *element_name,
    struct sbuf *sb, int *claimed)
{

	LABEL_CHECK(label, MAGIC_IFNET);
	COUNTER_INC(ifnet_externalize_label);

	return (0);
}