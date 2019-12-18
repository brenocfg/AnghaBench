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
struct pam_response {int dummy; } ;
struct pam_message {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  PAM_CONV_ERR ; 
 int /*<<< orphan*/  RETURNC (int /*<<< orphan*/ ) ; 

int
openpam_nullconv(int n,
	 const struct pam_message **msg,
	 struct pam_response **resp,
	 void *data)
{

	ENTER();
	(void)n;
	(void)msg;
	(void)resp;
	(void)data;
	RETURNC(PAM_CONV_ERR);
}