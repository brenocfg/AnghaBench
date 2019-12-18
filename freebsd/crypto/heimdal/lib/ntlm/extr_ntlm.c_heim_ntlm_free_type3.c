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
struct ntlm_type3 {int /*<<< orphan*/  sessionkey; scalar_t__ ws; scalar_t__ username; scalar_t__ targetname; int /*<<< orphan*/  ntlm; int /*<<< orphan*/  lm; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  heim_ntlm_free_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ntlm_type3*,int /*<<< orphan*/ ,int) ; 

void
heim_ntlm_free_type3(struct ntlm_type3 *data)
{
    heim_ntlm_free_buf(&data->lm);
    heim_ntlm_free_buf(&data->ntlm);
    if (data->targetname)
	free(data->targetname);
    if (data->username)
	free(data->username);
    if (data->ws)
	free(data->ws);
    heim_ntlm_free_buf(&data->sessionkey);
    memset(data, 0, sizeof(*data));
}