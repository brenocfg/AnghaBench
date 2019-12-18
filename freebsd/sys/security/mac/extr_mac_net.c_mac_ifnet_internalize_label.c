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
 int /*<<< orphan*/  MAC_POLICY_INTERNALIZE (int /*<<< orphan*/ ,struct label*,char*) ; 
 int /*<<< orphan*/  ifnet ; 

__attribute__((used)) static int
mac_ifnet_internalize_label(struct label *label, char *string)
{
	int error;

	MAC_POLICY_INTERNALIZE(ifnet, label, string);

	return (error);
}