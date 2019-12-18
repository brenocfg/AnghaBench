#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ len; } ;
typedef  TYPE_1__ token_t ;
struct TYPE_7__ {scalar_t__ used; scalar_t__ len; int /*<<< orphan*/  token_q; } ;
typedef  TYPE_2__ au_record_t ;

/* Variables and functions */
 scalar_t__ AUDIT_TRAILER_SIZE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ MAX_AUDIT_RECORD_SIZE ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_2__** open_desc_table ; 
 int /*<<< orphan*/  tokens ; 

int
au_write(int d, token_t *tok)
{
	au_record_t *rec;

	if (tok == NULL) {
		errno = EINVAL;
		return (-1); /* Invalid Token */
	}

	/* Write the token to the record descriptor */
	rec = open_desc_table[d];
	if ((rec == NULL) || (rec->used == 0)) {
		errno = EINVAL;
		return (-1); /* Invalid descriptor */
	}

	if (rec->len + tok->len + AUDIT_TRAILER_SIZE > MAX_AUDIT_RECORD_SIZE) {
		errno = ENOMEM;
		return (-1);
	}

	/* Add the token to the tail */
	/*
	 * XXX Not locking here -- we should not be writing to
	 * XXX the same descriptor from different threads
	 */
	TAILQ_INSERT_TAIL(&rec->token_q, tok, tokens);

	rec->len += tok->len; /* grow record length by token size bytes */

	/* Token should not be available after this call */
	tok = NULL;
	return (0); /* Success */
}