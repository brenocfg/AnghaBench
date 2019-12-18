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
typedef  int /*<<< orphan*/  progSep ;
typedef  int /*<<< orphan*/  nl ;

/* Variables and functions */
 int /*<<< orphan*/  STDERR_FILENO ; 
 char const* _getprogname () ; 
 int /*<<< orphan*/  _write (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
__env_warnx(const char *msg, const char *name, size_t nameLen)
{
	static const char nl[] = "\n";
	static const char progSep[] = ": ";

	_write(STDERR_FILENO, _getprogname(), strlen(_getprogname()));
	_write(STDERR_FILENO, progSep, sizeof(progSep) - 1);
	_write(STDERR_FILENO, msg, strlen(msg));
	_write(STDERR_FILENO, name, nameLen);
	_write(STDERR_FILENO, nl, sizeof(nl) - 1);

	return;
}