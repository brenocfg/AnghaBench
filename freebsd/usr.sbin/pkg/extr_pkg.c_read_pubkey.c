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
struct sbuf {int dummy; } ;
struct pubkey {int siglen; void* sig; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 void* calloc (int,int) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  sbuf_bcat (struct sbuf*,char*,int) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int sbuf_len (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static struct pubkey *
read_pubkey(int fd)
{
	struct pubkey *pk;
	struct sbuf *sig;
	char buf[4096];
	int r;

	if (lseek(fd, 0, 0) == -1) {
		warn("lseek");
		return (NULL);
	}

	sig = sbuf_new_auto();

	while ((r = read(fd, buf, sizeof(buf))) >0) {
		sbuf_bcat(sig, buf, r);
	}

	sbuf_finish(sig);
	pk = calloc(1, sizeof(struct pubkey));
	pk->siglen = sbuf_len(sig);
	pk->sig = calloc(1, pk->siglen);
	memcpy(pk->sig, sbuf_data(sig), pk->siglen);
	sbuf_delete(sig);

	return (pk);
}