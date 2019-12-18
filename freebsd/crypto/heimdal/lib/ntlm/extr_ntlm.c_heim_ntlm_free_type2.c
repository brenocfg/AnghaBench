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
struct ntlm_type2 {int /*<<< orphan*/  targetinfo; scalar_t__ targetname; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  heim_ntlm_free_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ntlm_type2*,int /*<<< orphan*/ ,int) ; 

void
heim_ntlm_free_type2(struct ntlm_type2 *data)
{
    if (data->targetname)
	free(data->targetname);
    heim_ntlm_free_buf(&data->targetinfo);
    memset(data, 0, sizeof(*data));
}