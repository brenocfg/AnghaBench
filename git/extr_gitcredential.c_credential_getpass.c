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
struct credential {void* password; void* username; } ;

/* Variables and functions */
 int PROMPT_ASKPASS ; 
 int PROMPT_ECHO ; 
 void* credential_ask_one (char*,struct credential*,int) ; 

__attribute__((used)) static void credential_getpass(struct credential *c)
{
	if (!c->username)
		c->username = credential_ask_one("Username", c,
						 PROMPT_ASKPASS|PROMPT_ECHO);
	if (!c->password)
		c->password = credential_ask_one("Password", c,
						 PROMPT_ASKPASS);
}