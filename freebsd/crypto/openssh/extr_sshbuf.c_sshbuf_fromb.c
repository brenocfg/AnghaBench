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

/* Variables and functions */
 scalar_t__ sshbuf_check_sanity (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 struct sshbuf* sshbuf_from (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_len (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_ptr (struct sshbuf*) ; 
 scalar_t__ sshbuf_set_parent (struct sshbuf*,struct sshbuf*) ; 

struct sshbuf *
sshbuf_fromb(struct sshbuf *buf)
{
	struct sshbuf *ret;

	if (sshbuf_check_sanity(buf) != 0)
		return NULL;
	if ((ret = sshbuf_from(sshbuf_ptr(buf), sshbuf_len(buf))) == NULL)
		return NULL;
	if (sshbuf_set_parent(ret, buf) != 0) {
		sshbuf_free(ret);
		return NULL;
	}
	return ret;
}