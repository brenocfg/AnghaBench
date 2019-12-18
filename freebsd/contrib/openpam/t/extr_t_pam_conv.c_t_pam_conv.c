#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct t_pam_conv_script {int nmsg; int /*<<< orphan*/ * comment; TYPE_2__* resps; TYPE_1__* msgs; } ;
struct pam_response {struct pam_response* resp; int /*<<< orphan*/  resp_retcode; } ;
struct pam_message {int msg_style; int /*<<< orphan*/  msg; } ;
struct TYPE_4__ {int /*<<< orphan*/  resp_retcode; int /*<<< orphan*/ * resp; } ;
struct TYPE_3__ {int msg_style; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int PAM_CONV_ERR ; 
#define  PAM_ERROR_MSG 131 
 int PAM_MAX_NUM_MSG ; 
#define  PAM_PROMPT_ECHO_OFF 130 
#define  PAM_PROMPT_ECHO_ON 129 
 int PAM_SUCCESS ; 
#define  PAM_TEXT_INFO 128 
 int /*<<< orphan*/  asprintf (int /*<<< orphan*/ **,char*,int,...) ; 
 struct pam_response* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct pam_response*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pam_response* strdup (int /*<<< orphan*/ *) ; 
 int strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t_printv (char*,int /*<<< orphan*/ ) ; 

int
t_pam_conv(int nm, const struct pam_message **msgs,
    struct pam_response **respsp, void *ad)
{
	struct t_pam_conv_script *s = ad;
	struct pam_response *resps;
	int i;

	/* check message count */
	if (nm != s->nmsg) {
		asprintf(&s->comment, "expected %d messages, got %d",
		    s->nmsg, nm);
		return (PAM_CONV_ERR);
	}
	if (nm <= 0 || nm > PAM_MAX_NUM_MSG) {
		/* since the previous test passed, this is intentional! */
		s->comment = NULL;
		return (PAM_CONV_ERR);
	}

	/* check each message and provide the sed answer */
	if ((resps = calloc(nm, sizeof *resps)) == NULL)
		goto enomem;
	for (i = 0; i < nm; ++i) {
		if (msgs[i]->msg_style != s->msgs[i].msg_style) {
			asprintf(&s->comment,
			    "message %d expected style %d got %d", i,
			    s->msgs[i].msg_style, msgs[i]->msg_style);
			goto fail;
		}
		if (strcmp(msgs[i]->msg, s->msgs[i].msg) != 0) {
			asprintf(&s->comment,
			    "message %d expected \"%s\" got \"%s\"", i,
			    s->msgs[i].msg, msgs[i]->msg);
			goto fail;
		}
		switch (msgs[i]->msg_style) {
		case PAM_PROMPT_ECHO_OFF:
			t_printv("[PAM_PROMPT_ECHO_OFF] %s\n", msgs[i]->msg);
			break;
		case PAM_PROMPT_ECHO_ON:
			t_printv("[PAM_PROMPT_ECHO_ON] %s\n", msgs[i]->msg);
			break;
		case PAM_ERROR_MSG:
			t_printv("[PAM_ERROR_MSG] %s\n", msgs[i]->msg);
			break;
		case PAM_TEXT_INFO:
			t_printv("[PAM_TEXT_INFO] %s\n", msgs[i]->msg);
			break;
		default:
			asprintf(&s->comment, "invalid message style %d",
			    msgs[i]->msg_style);
			goto fail;
		}
		/* copy the response, if there is one */
		if (s->resps[i].resp != NULL &&
		    (resps[i].resp = strdup(s->resps[i].resp)) == NULL)
			goto enomem;
		resps[i].resp_retcode = s->resps[i].resp_retcode;
	}
	s->comment = NULL;
	*respsp = resps;
	return (PAM_SUCCESS);
enomem:
	asprintf(&s->comment, "%s", strerror(ENOMEM));
fail:
	for (i = 0; i < nm; ++i)
		free(resps[i].resp);
	free(resps);
	return (PAM_CONV_ERR);
}