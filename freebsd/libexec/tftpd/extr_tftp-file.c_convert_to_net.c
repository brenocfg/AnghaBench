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

/* Variables and functions */
 char* convbuffer ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
convert_to_net(char *buffer, size_t count, int init)
{
	size_t i;
	static size_t n = 0, in = 0;
	static int newline = -1;

	if (init) {
		newline = -1;
		n = 0;
		in = 0;
		return 0 ;
	}

	/*
	 * Convert all LF to CR,LF and all CR to CR,NUL
	 */
	i = 0;

	if (newline != -1) {
		buffer[i++] = newline;
		newline = -1;
	}

	while (i < count) {
		if (n == in) {
			/* When done we're done */
			if (feof(file)) break;

			/* Otherwise read another bunch */
			in = fread(convbuffer, 1, count, file);
			if (in == 0) break;
			n = 0;
		}

		/* CR -> CR,NULL */
		if (convbuffer[n] == '\r') {
			buffer[i++] = '\r';
			buffer[i++] = '\0';
			n++;
			continue;
		}

		/* LF -> CR,LF */
		if (convbuffer[n] == '\n') {
			buffer[i++] = '\r';
			buffer[i++] = '\n';
			n++;
			continue;
		}

		buffer[i++] = convbuffer[n++];
	}

	if (i > count) {
		/*
		 * Whoops... that isn't allowed (but it will happen
		 * when there is a CR or LF at the end of the buffer)
		 */
		newline = buffer[i-1];
	}

	if (i < count) {
		/* We are done! */
		return i;
	} else
		return count;

}