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
struct sshbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int handle_from_string (int /*<<< orphan*/ *,size_t) ; 
 int sshbuf_get_string (struct sshbuf*,int /*<<< orphan*/ **,size_t*) ; 

__attribute__((used)) static int
get_handle(struct sshbuf *queue, int *hp)
{
	u_char *handle;
	int r;
	size_t hlen;

	*hp = -1;
	if ((r = sshbuf_get_string(queue, &handle, &hlen)) != 0)
		return r;
	if (hlen < 256)
		*hp = handle_from_string(handle, hlen);
	free(handle);
	return 0;
}