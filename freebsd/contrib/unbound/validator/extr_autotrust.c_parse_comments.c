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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ time_t ;
struct autr_ta {int s; scalar_t__ last_change; scalar_t__ pending_count; } ;

/* Variables and functions */
#define  AUTR_STATE_ADDPEND 133 
#define  AUTR_STATE_MISSING 132 
#define  AUTR_STATE_REMOVED 131 
#define  AUTR_STATE_REVOKED 130 
#define  AUTR_STATE_START 129 
#define  AUTR_STATE_VALID 128 
 int /*<<< orphan*/  VERB_OPS ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ malloc (int) ; 
 int position_in_string (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  verbose_key (struct autr_ta*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
parse_comments(char* str, struct autr_ta* ta)
{
        int len = (int)strlen(str), pos = 0, timestamp = 0;
        char* comment = (char*) malloc(sizeof(char)*len+1);
        char* comments = comment;
	if(!comment) {
		log_err("malloc failure in parse");
                return 0;
	}
	/* skip over whitespace and data at start of line */
        while (*str != '\0' && *str != ';')
                str++;
        if (*str == ';')
                str++;
        /* copy comments */
        while (*str != '\0')
        {
                *comments = *str;
                comments++;
                str++;
        }
        *comments = '\0';

        comments = comment;

        /* read state */
        pos = position_in_string(comments, "state=");
        if (pos >= (int) strlen(comments))
        {
		log_err("parse error");
                free(comment);
                return 0;
        }
        if (pos <= 0)
                ta->s = AUTR_STATE_VALID;
        else
        {
                int s = (int) comments[pos] - '0';
                switch(s)
                {
                        case AUTR_STATE_START:
                        case AUTR_STATE_ADDPEND:
                        case AUTR_STATE_VALID:
                        case AUTR_STATE_MISSING:
                        case AUTR_STATE_REVOKED:
                        case AUTR_STATE_REMOVED:
                                ta->s = s;
                                break;
                        default:
				verbose_key(ta, VERB_OPS, "has undefined "
					"state, considered NewKey");
                                ta->s = AUTR_STATE_START;
                                break;
                }
        }
        /* read pending count */
        pos = position_in_string(comments, "count=");
        if (pos >= (int) strlen(comments))
        {
		log_err("parse error");
                free(comment);
                return 0;
        }
        if (pos <= 0)
                ta->pending_count = 0;
        else
        {
                comments += pos;
                ta->pending_count = (uint8_t)atoi(comments);
        }

        /* read last change */
        pos = position_in_string(comments, "lastchange=");
        if (pos >= (int) strlen(comments))
        {
		log_err("parse error");
                free(comment);
                return 0;
        }
        if (pos >= 0)
        {
                comments += pos;
                timestamp = atoi(comments);
        }
        if (pos < 0 || !timestamp)
		ta->last_change = 0;
        else
                ta->last_change = (time_t)timestamp;

        free(comment);
        return 1;
}