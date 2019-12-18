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
typedef  int /*<<< orphan*/  u_char ;
struct sshkey {int dummy; } ;
struct sshbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int sshbuf_get_cstring (struct sshbuf*,char**,int /*<<< orphan*/ *) ; 
 int sshbuf_get_string_direct (struct sshbuf*,int /*<<< orphan*/  const**,size_t*) ; 
 int sshkey_from_blob (int /*<<< orphan*/  const*,size_t,struct sshkey**) ; 

__attribute__((used)) static int
deserialise_identity2(struct sshbuf *ids, struct sshkey **keyp, char **commentp)
{
	int r;
	char *comment = NULL;
	const u_char *blob;
	size_t blen;

	if ((r = sshbuf_get_string_direct(ids, &blob, &blen)) != 0 ||
	    (r = sshbuf_get_cstring(ids, &comment, NULL)) != 0)
		goto out;
	if ((r = sshkey_from_blob(blob, blen, keyp)) != 0)
		goto out;
	if (commentp != NULL) {
		*commentp = comment;
		comment = NULL;
	}
	r = 0;
 out:
	free(comment);
	return r;
}