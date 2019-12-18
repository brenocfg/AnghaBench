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
struct pam_response {int /*<<< orphan*/ * resp; scalar_t__ resp_retcode; } ;
struct pam_message {scalar_t__ msg_style; } ;

/* Variables and functions */
 int PAM_CONV_ERR ; 
 scalar_t__ PAM_PROMPT_ECHO_OFF ; 
 int PAM_SUCCESS ; 
 struct pam_response* malloc (int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static int
pam_conv(int n, const struct pam_message **msg, struct pam_response **resp,
  void *data)
{

  if (n != 1 || msg[0]->msg_style != PAM_PROMPT_ECHO_OFF)
    return (PAM_CONV_ERR);
  if ((*resp = malloc(sizeof(struct pam_response))) == NULL)
    return (PAM_CONV_ERR);
  (*resp)[0].resp = strdup((const char *)data);
  (*resp)[0].resp_retcode = 0;

  return ((*resp)[0].resp != NULL ? PAM_SUCCESS : PAM_CONV_ERR);
}