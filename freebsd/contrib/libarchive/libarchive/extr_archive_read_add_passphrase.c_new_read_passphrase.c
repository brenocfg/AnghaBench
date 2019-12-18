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
struct archive_read_passphrase {int /*<<< orphan*/ * passphrase; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct archive_read_passphrase*) ; 
 struct archive_read_passphrase* malloc (int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static struct archive_read_passphrase *
new_read_passphrase(struct archive_read *a, const char *passphrase)
{
	struct archive_read_passphrase *p;

	p = malloc(sizeof(*p));
	if (p == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory");
		return (NULL);
	}
	p->passphrase = strdup(passphrase);
	if (p->passphrase == NULL) {
		free(p);
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory");
		return (NULL);
	}
	return (p);
}