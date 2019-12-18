#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ from_state; int /*<<< orphan*/  name; int /*<<< orphan*/ * ns; } ;
typedef  TYPE_3__ svn_ra_serf__xml_transition_t ;
struct TYPE_9__ {int /*<<< orphan*/  scratch_pool; TYPE_3__* ttable; int /*<<< orphan*/  free_states; TYPE_2__* current; } ;
typedef  TYPE_4__ svn_ra_serf__xml_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {char const* name; } ;
struct TYPE_7__ {TYPE_1__ tag; scalar_t__ prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_XML_MALFORMED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ XML_STATE_INITIAL ; 
 char* _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_ra_serf__xml_context_done(svn_ra_serf__xml_context_t *xmlctx)
{
  if (xmlctx->current->prev)
    {
      /* Probably unreachable as this would be an xml parser error */
      return svn_error_createf(SVN_ERR_XML_MALFORMED, NULL,
                               _("XML stream truncated: closing '%s' missing"),
                               xmlctx->current->tag.name);
    }
  else if (! xmlctx->free_states)
    {
      /* If we have no items on the free_states list, we didn't push anything,
         which tells us that we found an empty xml body */
      const svn_ra_serf__xml_transition_t *scan;
      const svn_ra_serf__xml_transition_t *document = NULL;
      const char *msg;

      for (scan = xmlctx->ttable; scan->ns != NULL; ++scan)
        {
          if (scan->from_state == XML_STATE_INITIAL)
            {
              if (document != NULL)
                {
                  document = NULL; /* Multiple document elements defined */
                  break;
                }
              document = scan;
            }
        }

      if (document)
        msg = apr_psprintf(xmlctx->scratch_pool, "'%s' element not found",
                            document->name);
      else
        msg = _("document element not found");

      return svn_error_createf(SVN_ERR_XML_MALFORMED, NULL,
                               _("XML stream truncated: %s"),
                               msg);
    }

  svn_pool_destroy(xmlctx->scratch_pool);
  return SVN_NO_ERROR;
}