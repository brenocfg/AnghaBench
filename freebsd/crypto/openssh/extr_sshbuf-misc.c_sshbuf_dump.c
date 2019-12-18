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
struct sshbuf {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,struct sshbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_dump_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshbuf_len (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_ptr (struct sshbuf*) ; 

void
sshbuf_dump(struct sshbuf *buf, FILE *f)
{
	fprintf(f, "buffer %p len = %zu\n", buf, sshbuf_len(buf));
	sshbuf_dump_data(sshbuf_ptr(buf), sshbuf_len(buf), f);
}