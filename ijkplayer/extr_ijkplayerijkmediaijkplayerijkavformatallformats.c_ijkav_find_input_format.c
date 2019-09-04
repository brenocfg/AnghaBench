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
struct AVInputFormat {int /*<<< orphan*/  name; } ;
typedef  struct AVInputFormat AVInputFormat ;

/* Variables and functions */
 struct AVInputFormat* av_iformat_next (struct AVInputFormat*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct AVInputFormat *ijkav_find_input_format(const char *iformat_name)
{
    AVInputFormat *fmt = NULL;
    if (!iformat_name)
        return NULL;
    while ((fmt = av_iformat_next(fmt))) {
        if (!fmt->name)
            continue;
        if (!strcmp(iformat_name, fmt->name))
            return fmt;
    }
    return NULL;
}