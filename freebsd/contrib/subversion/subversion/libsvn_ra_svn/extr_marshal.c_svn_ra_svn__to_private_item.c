#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  list; int /*<<< orphan*/  word; int /*<<< orphan*/  number; int /*<<< orphan*/ * string; } ;
struct TYPE_11__ {int kind; TYPE_3__ u; } ;
typedef  TYPE_4__ svn_ra_svn_item_t ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int /*<<< orphan*/  list; TYPE_1__ word; int /*<<< orphan*/  number; int /*<<< orphan*/  string; } ;
struct TYPE_12__ {int kind; TYPE_2__ u; } ;
typedef  TYPE_5__ svn_ra_svn__item_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
#define  SVN_RA_SVN_LIST 131 
#define  SVN_RA_SVN_NUMBER 130 
#define  SVN_RA_SVN_STRING 129 
#define  SVN_RA_SVN_WORD 128 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_ra_svn__to_private_array (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
svn_ra_svn__to_private_item(svn_ra_svn__item_t *target,
                            const svn_ra_svn_item_t *source,
                            apr_pool_t *result_pool)
{
  target->kind = source->kind;
  switch (source->kind)
    {
      case SVN_RA_SVN_STRING:
        target->u.string = *source->u.string;
        break;
      case SVN_RA_SVN_NUMBER:
        target->u.number = source->u.number;
        break;
      case SVN_RA_SVN_WORD:
        target->u.word.data = source->u.word;
        target->u.word.len = strlen(source->u.word);
        break;
      case SVN_RA_SVN_LIST:
        target->u.list = *svn_ra_svn__to_private_array(source->u.list,
                                                       result_pool);
        break;
    }
}