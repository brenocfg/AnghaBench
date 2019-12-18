#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_compat_log_revprops_out_string (TYPE_1__ const**,TYPE_1__ const**,TYPE_1__ const**,int /*<<< orphan*/ *) ; 

void
svn_compat_log_revprops_out(const char **author, const char **date,
                            const char **message, apr_hash_t *revprops)
{
  const svn_string_t *author_s, *date_s,  *message_s;
  svn_compat_log_revprops_out_string(&author_s, &date_s,  &message_s,
                                     revprops);

  *author = author_s ? author_s->data : NULL;
  *date = date_s ? date_s->data : NULL;
  *message = message_s ? message_s->data : NULL;
}