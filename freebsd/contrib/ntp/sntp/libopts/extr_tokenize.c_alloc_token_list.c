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
struct TYPE_4__ {int /*<<< orphan*/ ** tkn_list; } ;
typedef  TYPE_1__ token_list_t ;
typedef  int /*<<< orphan*/  ch_t ;

/* Variables and functions */
 char* BRK_WHITESPACE_CHARS (char const*) ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 char const NUL ; 
 char* SPN_WHITESPACE_CHARS (char const*) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static token_list_t *
alloc_token_list(char const * str)
{
    token_list_t * res;

    int max_token_ct = 2; /* allow for trailing NULL pointer & NUL on string */

    if (str == NULL) goto enoent_res;

    /*
     *  Trim leading white space.  Use "ENOENT" and a NULL return to indicate
     *  an empty string was passed.
     */
    str = SPN_WHITESPACE_CHARS(str);
    if (*str == NUL)  goto enoent_res;

    /*
     *  Take an approximate count of tokens.  If no quoted strings are used,
     *  it will be accurate.  If quoted strings are used, it will be a little
     *  high and we'll squander the space for a few extra pointers.
     */
    {
        char const * pz = str;

        do {
            max_token_ct++;
            pz = BRK_WHITESPACE_CHARS(pz+1);
            pz = SPN_WHITESPACE_CHARS(pz);
        } while (*pz != NUL);

        res = malloc(sizeof(*res) + (size_t)(pz - str)
                     + ((size_t)max_token_ct * sizeof(ch_t *)));
    }

    if (res == NULL)
        errno = ENOMEM;
    else res->tkn_list[0] = (ch_t *)(res->tkn_list + (max_token_ct - 1));

    return res;

    enoent_res:

    errno = ENOENT;
    return NULL;
}