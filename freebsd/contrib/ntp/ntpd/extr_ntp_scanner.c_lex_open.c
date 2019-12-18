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
struct TYPE_2__ {int nline; } ;
struct FILE_INFO {int /*<<< orphan*/ * fpi; int /*<<< orphan*/  fname; int /*<<< orphan*/  backch; TYPE_1__ curpos; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOF ; 
 struct FILE_INFO* emalloc_zero (int) ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/  free (struct FILE_INFO*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static struct FILE_INFO *
lex_open(
	const char *path,
	const char *mode
	)
{
	struct FILE_INFO *stream;
	size_t            nnambuf;

	nnambuf = strlen(path);
	stream = emalloc_zero(sizeof(*stream) + nnambuf);
	stream->curpos.nline = 1;
	stream->backch = EOF;
	/* copy name with memcpy -- trailing NUL already there! */
	memcpy(stream->fname, path, nnambuf);

	if (NULL != mode) {
		stream->fpi = fopen(path, mode);
		if (NULL == stream->fpi) {
			free(stream);
			stream = NULL;
		}
	}
	return stream;
}