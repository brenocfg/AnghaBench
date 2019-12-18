#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {size_t len; int /*<<< orphan*/  t_data; } ;
typedef  TYPE_1__ token_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  au_free_token (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

int
au_close_token(token_t *tok, u_char *buffer, size_t *buflen)
{

	if (tok->len > *buflen) {
		au_free_token(tok);
		errno = ENOMEM;
		return (EINVAL);
	}

	memcpy(buffer, tok->t_data, tok->len);
	*buflen = tok->len;
	au_free_token(tok);
	return (0);
}