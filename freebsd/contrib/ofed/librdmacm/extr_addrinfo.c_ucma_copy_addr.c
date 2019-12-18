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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int ERR (int /*<<< orphan*/ ) ; 
 struct sockaddr* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucma_copy_addr(struct sockaddr **dst, socklen_t *dst_len,
			  struct sockaddr *src, socklen_t src_len)
{
	*dst = malloc(src_len);
	if (!(*dst))
		return ERR(ENOMEM);

	memcpy(*dst, src, src_len);
	*dst_len = src_len;
	return 0;
}