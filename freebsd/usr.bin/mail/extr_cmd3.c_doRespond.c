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
struct message {int dummy; } ;
struct header {char* h_inreplyto; int /*<<< orphan*/  h_replyto; int /*<<< orphan*/ * h_smopts; int /*<<< orphan*/ * h_bcc; int /*<<< orphan*/ * h_cc; int /*<<< orphan*/ * h_subject; int /*<<< orphan*/ * h_to; } ;

/* Variables and functions */
 int /*<<< orphan*/  GTO ; 
 int /*<<< orphan*/ * cat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct message* dot ; 
 int /*<<< orphan*/  extract (char*,int /*<<< orphan*/ ) ; 
 void* hfield (char*,struct message*) ; 
 int /*<<< orphan*/  mail1 (struct header*,int) ; 
 struct message* message ; 
 void* nameof (struct message*,int) ; 
 int /*<<< orphan*/ * reedit (int /*<<< orphan*/ *) ; 
 char* skin (void*) ; 
 int /*<<< orphan*/  touch (struct message*) ; 
 int /*<<< orphan*/  value (char*) ; 

int
doRespond(int msgvec[])
{
	struct header head;
	struct message *mp;
	int *ap;
	char *cp, *mid;

	head.h_to = NULL;
	for (ap = msgvec; *ap != 0; ap++) {
		mp = &message[*ap - 1];
		touch(mp);
		dot = mp;
		if ((cp = skin(hfield("from", mp))) == NULL)
			cp = skin(nameof(mp, 2));
		head.h_to = cat(head.h_to, extract(cp, GTO));
		mid = skin(hfield("message-id", mp));
	}
	if (head.h_to == NULL)
		return (0);
	mp = &message[msgvec[0] - 1];
	if ((head.h_subject = hfield("subject", mp)) == NULL)
		head.h_subject = hfield("subj", mp);
	head.h_subject = reedit(head.h_subject);
	head.h_cc = NULL;
	head.h_bcc = NULL;
	head.h_smopts = NULL;
	head.h_replyto = value("REPLYTO");
	head.h_inreplyto = mid;
	mail1(&head, 1);
	return (0);
}