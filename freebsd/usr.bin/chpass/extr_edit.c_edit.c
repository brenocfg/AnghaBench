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
struct passwd {int dummy; } ;

/* Variables and functions */
 int display (char const*,struct passwd*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* fgetln (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  free (struct passwd*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 struct passwd* pw_dup (struct passwd*) ; 
 int pw_edit (int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 struct passwd* verify (char const*,struct passwd*) ; 
 int /*<<< orphan*/  warn (char*) ; 

struct passwd *
edit(const char *tfn, struct passwd *pw)
{
	struct passwd *npw;
	char *line;
	size_t len;

	if (display(tfn, pw) == -1)
		return (NULL);
	for (;;) {
		switch (pw_edit(1)) {
		case -1:
			return (NULL);
		case 0:
			return (pw_dup(pw));
		default:
			break;
		}
		if ((npw = verify(tfn, pw)) != NULL)
			return (npw);
		free(npw);
		printf("re-edit the password file? ");
		fflush(stdout);
		if ((line = fgetln(stdin, &len)) == NULL) {
			warn("fgetln()");
			return (NULL);
		}
		if (len > 0 && (*line == 'N' || *line == 'n'))
			return (NULL);
	}
}