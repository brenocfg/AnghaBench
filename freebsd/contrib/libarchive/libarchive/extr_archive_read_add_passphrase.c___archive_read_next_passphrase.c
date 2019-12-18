#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct archive_read_passphrase {char* passphrase; struct archive_read_passphrase* next; } ;
struct TYPE_2__ {int candidate; char* (* callback ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  client_data; struct archive_read_passphrase* first; } ;
struct archive_read {TYPE_1__ passphrases; int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_passphrase_to_tail (struct archive_read*,struct archive_read_passphrase*) ; 
 int /*<<< orphan*/  insert_passphrase_to_head (struct archive_read*,struct archive_read_passphrase*) ; 
 struct archive_read_passphrase* new_read_passphrase (struct archive_read*,char const*) ; 
 struct archive_read_passphrase* remove_passphrases_from_head (struct archive_read*) ; 
 char* stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

const char *
__archive_read_next_passphrase(struct archive_read *a)
{
	struct archive_read_passphrase *p;
	const char *passphrase;

	if (a->passphrases.candidate < 0) {
		/* Count out how many passphrases we have. */
		int cnt = 0;

		for (p = a->passphrases.first; p != NULL; p = p->next)
			cnt++;
		a->passphrases.candidate = cnt;
		p = a->passphrases.first;
	} else if (a->passphrases.candidate > 1) {
		/* Rotate a passphrase list. */
		a->passphrases.candidate--;
		p = remove_passphrases_from_head(a);
		add_passphrase_to_tail(a, p);
		/* Pick a new passphrase candidate up. */
		p = a->passphrases.first;
	} else if (a->passphrases.candidate == 1) {
		/* This case is that all candidates failed to decrypt. */
		a->passphrases.candidate = 0;
		if (a->passphrases.first->next != NULL) {
			/* Rotate a passphrase list. */
			p = remove_passphrases_from_head(a);
			add_passphrase_to_tail(a, p);
		}
		p = NULL;
	} else  /* There is no passphrase candidate. */
		p = NULL;

	if (p != NULL)
		passphrase = p->passphrase;
	else if (a->passphrases.callback != NULL) {
		/* Get a passphrase through a call-back function
		 * since we tried all passphrases out or we don't
		 * have it. */
		passphrase = a->passphrases.callback(&a->archive,
		    a->passphrases.client_data);
		if (passphrase != NULL) {
			p = new_read_passphrase(a, passphrase);
			if (p == NULL)
				return (NULL);
			insert_passphrase_to_head(a, p);
			a->passphrases.candidate = 1;
		}
	} else
		passphrase = NULL;

	return (passphrase);
}