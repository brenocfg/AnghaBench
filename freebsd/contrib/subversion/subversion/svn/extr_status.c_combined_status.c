#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int node_status; int text_status; int /*<<< orphan*/  conflicted; int /*<<< orphan*/  versioned; } ;
typedef  TYPE_1__ svn_client_status_t ;
typedef  enum svn_wc_status_kind { ____Placeholder_svn_wc_status_kind } svn_wc_status_kind ;

/* Variables and functions */
#define  svn_wc_status_conflicted 129 
 int svn_wc_status_missing ; 
#define  svn_wc_status_modified 128 

__attribute__((used)) static enum svn_wc_status_kind
combined_status(const svn_client_status_t *status)
{
  enum svn_wc_status_kind new_status = status->node_status;

  switch (status->node_status)
    {
      case svn_wc_status_conflicted:
        if (!status->versioned && status->conflicted)
          {
            /* Report unversioned tree conflict victims as missing: '!' */
            new_status = svn_wc_status_missing;
            break;
          }
        /* fall through */
      case svn_wc_status_modified:
        /* This value might be the property status */
        new_status = status->text_status;
        break;
      default:
        break;
    }

  return new_status;
}