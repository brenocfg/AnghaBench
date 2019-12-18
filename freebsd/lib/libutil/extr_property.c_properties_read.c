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
typedef  TYPE_1__* properties ;
struct TYPE_4__ {struct TYPE_4__* next; } ;

/* Variables and functions */
 int BUFSIZ ; 
 int PROPERTY_MAX_NAME ; 
 int PROPERTY_MAX_VALUE ; 
 int /*<<< orphan*/  isalnum (unsigned char) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 int /*<<< orphan*/  properties_free (TYPE_1__*) ; 
 void* property_alloc (char*,char*) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

properties
properties_read(int fd)
{
    properties head, ptr;
    char hold_n[PROPERTY_MAX_NAME + 1];
    char hold_v[PROPERTY_MAX_VALUE + 1];
    char buf[BUFSIZ * 4];
    int bp, n, v, max;
    enum { LOOK, COMMENT, NAME, VALUE, MVALUE, COMMIT, FILL, STOP } state, last_state;
    int ch = 0, blevel = 0;

    n = v = bp = max = 0;
    head = ptr = NULL;
    state = last_state = LOOK;
    while (state != STOP) {
	if (state != COMMIT) {
	    if (bp == max) {
		last_state = state;
		state = FILL;
	    } else
		ch = buf[bp++];
	}
	switch(state) {
	case FILL:
	    if ((max = read(fd, buf, sizeof buf)) < 0) {
		properties_free(head);
		return (NULL);
	    }
	    if (max == 0) {
		state = STOP;
	    } else {
		/*
		 * Restore the state from before the fill (which will be
		 * initialised to LOOK for the first FILL). This ensures that
		 * if we were part-way through eg., a VALUE state, when the
		 * buffer ran out, that the previous operation will be allowed
		 * to complete.
		 */
		state = last_state;
		ch = buf[0];
		bp = 0;
	    }
	    continue;

	case LOOK:
	    if (isspace((unsigned char)ch))
		continue;
	    /* Allow shell or lisp style comments */
	    else if (ch == '#' || ch == ';') {
		state = COMMENT;
		continue;
	    }
	    else if (isalnum((unsigned char)ch) || ch == '_') {
		if (n >= PROPERTY_MAX_NAME) {
		    n = 0;
		    state = COMMENT;
		}
		else {
		    hold_n[n++] = ch;
		    state = NAME;
		}
	    }
	    else
		state = COMMENT;	/* Ignore the rest of the line */
	    break;

	case COMMENT:
	    if (ch == '\n')
		state = LOOK;
	    break;

	case NAME:
	    if (ch == '\n' || !ch) {
		hold_n[n] = '\0';
		hold_v[0] = '\0';
		v = n = 0;
		state = COMMIT;
	    }
	    else if (isspace((unsigned char)ch))
		continue;
	    else if (ch == '=') {
		hold_n[n] = '\0';
		v = n = 0;
		state = VALUE;
	    }
	    else
		hold_n[n++] = ch;
	    break;

	case VALUE:
	    if (v == 0 && ch == '\n') {
	        hold_v[v] = '\0';
	        v = n = 0;
	        state = COMMIT;
	    } 
	    else if (v == 0 && isspace((unsigned char)ch))
		continue;
	    else if (ch == '{') {
		state = MVALUE;
		++blevel;
	    }
	    else if (ch == '\n' || !ch) {
		hold_v[v] = '\0';
		v = n = 0;
		state = COMMIT;
	    }
	    else {
		if (v >= PROPERTY_MAX_VALUE) {
		    state = COMMENT;
		    v = n = 0;
		    break;
		}
		else
		    hold_v[v++] = ch;
	    }
	    break;

	case MVALUE:
	    /* multiline value */
	    if (v >= PROPERTY_MAX_VALUE) {
		warn("properties_read: value exceeds max length");
		state = COMMENT;
		n = v = 0;
	    }
	    else if (ch == '}' && !--blevel) {
		hold_v[v] = '\0';
		v = n = 0;
		state = COMMIT;
	    }
	    else {
		hold_v[v++] = ch;
		if (ch == '{')
		    ++blevel;
	    }
	    break;

	case COMMIT:
	    if (head == NULL) {
		if ((head = ptr = property_alloc(hold_n, hold_v)) == NULL)
		    return (NULL);
	    } else {
		if ((ptr->next = property_alloc(hold_n, hold_v)) == NULL) {
		    properties_free(head);
		    return (NULL);
		}
		ptr = ptr->next;
	    }
	    state = LOOK;
	    v = n = 0;
	    break;

	case STOP:
	    /* we don't handle this here, but this prevents warnings */
	    break;
	}
    }
    if (head == NULL && (head = property_alloc(NULL, NULL)) == NULL)
	return (NULL);

    return (head);
}