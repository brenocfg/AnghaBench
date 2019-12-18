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
struct message {scalar_t__ m_lines; scalar_t__ m_size; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Fclose (int /*<<< orphan*/ *) ; 
 struct message* dot ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct message* message ; 
 int msgCount ; 
 size_t read (int /*<<< orphan*/ ,void*,size_t) ; 
 scalar_t__ realloc (struct message*,size_t) ; 

void
makemessage(FILE *f, int omsgCount)
{
	size_t size;
	struct message *nmessage;

	size = (msgCount + 1) * sizeof(struct message);
	nmessage = (struct message *)realloc(message, size);
	if (nmessage == NULL)
		errx(1, "Insufficient memory for %d messages\n",
		    msgCount);
	if (omsgCount == 0 || message == NULL)
		dot = nmessage;
	else
		dot = nmessage + (dot - message);
	message = nmessage;
	size -= (omsgCount + 1) * sizeof(struct message);
	(void)fflush(f);
	(void)lseek(fileno(f), (off_t)sizeof(*message), 0);
	if (read(fileno(f), (void *)&message[omsgCount], size) != size)
		errx(1, "Message temporary file corrupted");
	message[msgCount].m_size = 0;
	message[msgCount].m_lines = 0;
	(void)Fclose(f);
}