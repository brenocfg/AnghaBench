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
struct TYPE_2__ {scalar_t__ pos_in_chain; int /*<<< orphan*/ * chain; } ;
struct evbuffer_ptr {scalar_t__ pos; TYPE_1__ internal_; } ;
struct evbuffer {int /*<<< orphan*/ * first; } ;
typedef  int /*<<< orphan*/  it ;
typedef  scalar_t__ ev_ssize_t ;
typedef  enum evbuffer_eol_style { ____Placeholder_evbuffer_eol_style } evbuffer_eol_style ;

/* Variables and functions */
#define  EVBUFFER_EOL_ANY 132 
#define  EVBUFFER_EOL_CRLF 131 
#define  EVBUFFER_EOL_CRLF_STRICT 130 
#define  EVBUFFER_EOL_LF 129 
#define  EVBUFFER_EOL_NUL 128 
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  PTR_NOT_FOUND (struct evbuffer_ptr*) ; 
 int /*<<< orphan*/  evbuffer_find_eol_char (struct evbuffer_ptr*) ; 
 char evbuffer_getchr (struct evbuffer_ptr*) ; 
 int /*<<< orphan*/  evbuffer_ptr_subtract (struct evbuffer*,struct evbuffer_ptr*,int) ; 
 struct evbuffer_ptr evbuffer_search (struct evbuffer*,char*,int,struct evbuffer_ptr*) ; 
 int /*<<< orphan*/  evbuffer_strchr (struct evbuffer_ptr*,char) ; 
 size_t evbuffer_strspn (struct evbuffer_ptr*,char*) ; 
 int /*<<< orphan*/  memcpy (struct evbuffer_ptr*,struct evbuffer_ptr*,int) ; 

struct evbuffer_ptr
evbuffer_search_eol(struct evbuffer *buffer,
    struct evbuffer_ptr *start, size_t *eol_len_out,
    enum evbuffer_eol_style eol_style)
{
	struct evbuffer_ptr it, it2;
	size_t extra_drain = 0;
	int ok = 0;

	/* Avoid locking in trivial edge cases */
	if (start && start->internal_.chain == NULL) {
		PTR_NOT_FOUND(&it);
		if (eol_len_out)
			*eol_len_out = extra_drain;
		return it;
	}

	EVBUFFER_LOCK(buffer);

	if (start) {
		memcpy(&it, start, sizeof(it));
	} else {
		it.pos = 0;
		it.internal_.chain = buffer->first;
		it.internal_.pos_in_chain = 0;
	}

	/* the eol_style determines our first stop character and how many
	 * characters we are going to drain afterwards. */
	switch (eol_style) {
	case EVBUFFER_EOL_ANY:
		if (evbuffer_find_eol_char(&it) < 0)
			goto done;
		memcpy(&it2, &it, sizeof(it));
		extra_drain = evbuffer_strspn(&it2, "\r\n");
		break;
	case EVBUFFER_EOL_CRLF_STRICT: {
		it = evbuffer_search(buffer, "\r\n", 2, &it);
		if (it.pos < 0)
			goto done;
		extra_drain = 2;
		break;
	}
	case EVBUFFER_EOL_CRLF: {
		ev_ssize_t start_pos = it.pos;
		/* Look for a LF ... */
		if (evbuffer_strchr(&it, '\n') < 0)
			goto done;
		extra_drain = 1;
		/* ... optionally preceeded by a CR. */
		if (it.pos == start_pos)
			break; /* If the first character is \n, don't back up */
		/* This potentially does an extra linear walk over the first
		 * few chains.  Probably, that's not too expensive unless you
		 * have a really pathological setup. */
		memcpy(&it2, &it, sizeof(it));
		if (evbuffer_ptr_subtract(buffer, &it2, 1)<0)
			break;
		if (evbuffer_getchr(&it2) == '\r') {
			memcpy(&it, &it2, sizeof(it));
			extra_drain = 2;
		}
		break;
	}
	case EVBUFFER_EOL_LF:
		if (evbuffer_strchr(&it, '\n') < 0)
			goto done;
		extra_drain = 1;
		break;
	case EVBUFFER_EOL_NUL:
		if (evbuffer_strchr(&it, '\0') < 0)
			goto done;
		extra_drain = 1;
		break;
	default:
		goto done;
	}

	ok = 1;
done:
	EVBUFFER_UNLOCK(buffer);

	if (!ok)
		PTR_NOT_FOUND(&it);
	if (eol_len_out)
		*eol_len_out = extra_drain;

	return it;
}