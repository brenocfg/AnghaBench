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
struct name {int dummy; } ;
struct message {int dummy; } ;
struct header {void* h_inreplyto; int /*<<< orphan*/  h_replyto; int /*<<< orphan*/ * h_smopts; int /*<<< orphan*/ * h_bcc; struct name* h_cc; int /*<<< orphan*/ * h_subject; struct name* h_to; } ;

/* Variables and functions */
 int /*<<< orphan*/  GCC ; 
 int /*<<< orphan*/  GTO ; 
 char** altnames ; 
 struct name* cat (struct name*,struct name*) ; 
 struct name* delname (struct name*,char*) ; 
 struct message* dot ; 
 struct name* elide (struct name*) ; 
 struct name* extract (char*,int /*<<< orphan*/ ) ; 
 void* hfield (char*,struct message*) ; 
 int /*<<< orphan*/  mail1 (struct header*,int) ; 
 struct message* message ; 
 char* myname ; 
 void* nameof (struct message*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * reedit (int /*<<< orphan*/ *) ; 
 void* skin (void*) ; 
 int /*<<< orphan*/  touch (struct message*) ; 
 int /*<<< orphan*/  value (char*) ; 

int
dorespond(int *msgvec)
{
	struct message *mp;
	char *cp, *rcv, *replyto;
	char **ap;
	struct name *np;
	struct header head;

	if (msgvec[1] != 0) {
		printf("Sorry, can't reply to multiple messages at once\n");
		return (1);
	}
	mp = &message[msgvec[0] - 1];
	touch(mp);
	dot = mp;
	if ((rcv = skin(hfield("from", mp))) == NULL)
		rcv = skin(nameof(mp, 1));
	if ((replyto = skin(hfield("reply-to", mp))) != NULL)
		np = extract(replyto, GTO);
	else if ((cp = skin(hfield("to", mp))) != NULL)
		np = extract(cp, GTO);
	else
		np = NULL;
	np = elide(np);
	/*
	 * Delete my name from the reply list,
	 * and with it, all my alternate names.
	 */
	np = delname(np, myname);
	if (altnames)
		for (ap = altnames; *ap != NULL; ap++)
			np = delname(np, *ap);
	if (np != NULL && replyto == NULL)
		np = cat(np, extract(rcv, GTO));
	else if (np == NULL) {
		if (replyto != NULL)
			printf("Empty reply-to field -- replying to author\n");
		np = extract(rcv, GTO);
	}
	head.h_to = np;
	if ((head.h_subject = hfield("subject", mp)) == NULL)
		head.h_subject = hfield("subj", mp);
	head.h_subject = reedit(head.h_subject);
	if (replyto == NULL && (cp = skin(hfield("cc", mp))) != NULL) {
		np = elide(extract(cp, GCC));
		np = delname(np, myname);
		if (altnames != 0)
			for (ap = altnames; *ap != NULL; ap++)
				np = delname(np, *ap);
		head.h_cc = np;
	} else
		head.h_cc = NULL;
	head.h_bcc = NULL;
	head.h_smopts = NULL;
	head.h_replyto = value("REPLYTO");
	head.h_inreplyto = skin(hfield("message-id", mp));
	mail1(&head, 1);
	return (0);
}