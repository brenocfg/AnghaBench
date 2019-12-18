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
struct FILE_INFO {int /*<<< orphan*/ * fpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct FILE_INFO*) ; 

__attribute__((used)) static void
lex_close(
	struct FILE_INFO *stream
	)
{
	if (NULL != stream) {
		if (NULL != stream->fpi)
			fclose(stream->fpi);		
		free(stream);
	}
}