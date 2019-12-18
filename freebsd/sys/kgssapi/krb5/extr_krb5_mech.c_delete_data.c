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
struct krb5_data {int /*<<< orphan*/ * kd_data; scalar_t__ kd_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
delete_data(struct krb5_data *dp)
{
	if (dp->kd_data) {
		free(dp->kd_data, M_GSSAPI);
		dp->kd_length = 0;
		dp->kd_data = NULL;
	}
}