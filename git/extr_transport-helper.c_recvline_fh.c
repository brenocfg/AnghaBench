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
struct strbuf {char* buf; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static int recvline_fh(FILE *helper, struct strbuf *buffer)
{
	strbuf_reset(buffer);
	if (debug)
		fprintf(stderr, "Debug: Remote helper: Waiting...\n");
	if (strbuf_getline(buffer, helper) == EOF) {
		if (debug)
			fprintf(stderr, "Debug: Remote helper quit.\n");
		return 1;
	}

	if (debug)
		fprintf(stderr, "Debug: Remote helper: <- %s\n", buffer->buf);
	return 0;
}