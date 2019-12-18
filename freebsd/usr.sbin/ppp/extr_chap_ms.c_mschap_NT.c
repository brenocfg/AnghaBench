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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  ChallengeResponse (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 

void
mschap_NT(char *passwordHash, char *challenge)
{
    u_char response[24];

    ChallengeResponse(challenge, passwordHash, response);
    memcpy(passwordHash, response, 24);
    passwordHash[24] = 1;		/* NT-style response */
}