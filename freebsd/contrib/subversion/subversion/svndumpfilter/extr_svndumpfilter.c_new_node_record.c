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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct revmap_t {int /*<<< orphan*/  rev; } ;
struct parse_baton_t {int /*<<< orphan*/  renumber_history; scalar_t__ do_renumber_revs; int /*<<< orphan*/  glob; int /*<<< orphan*/  do_exclude; int /*<<< orphan*/  prefixes; int /*<<< orphan*/ * dropped_nodes; } ;
struct node_baton_t {char* node_path; int /*<<< orphan*/  headers; void* has_text_delta; void* has_prop_delta; TYPE_1__* rb; int /*<<< orphan*/  props; int /*<<< orphan*/  tcl; void* writing_begun; void* has_text; void* has_props; scalar_t__ do_skip; int /*<<< orphan*/ * node_pool; } ;
typedef  int /*<<< orphan*/  cf_orig_rev ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_2__ {int /*<<< orphan*/  writing_begun; void* has_nodes; void* had_dropped_nodes; struct parse_baton_t* pb; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_INCOMPLETE_DATA ; 
 int /*<<< orphan*/  SVN_ERR_NODE_UNEXPECTED_KIND ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* SVN_REPOS_DUMPFILE_CONTENT_LENGTH ; 
 char* SVN_REPOS_DUMPFILE_NODE_ACTION ; 
 char* SVN_REPOS_DUMPFILE_NODE_COPYFROM_PATH ; 
 char* SVN_REPOS_DUMPFILE_NODE_COPYFROM_REV ; 
 char* SVN_REPOS_DUMPFILE_NODE_KIND ; 
 char* SVN_REPOS_DUMPFILE_NODE_PATH ; 
 char* SVN_REPOS_DUMPFILE_PROP_CONTENT_LENGTH ; 
 char* SVN_REPOS_DUMPFILE_PROP_DELTA ; 
 char* SVN_REPOS_DUMPFILE_TEXT_CONTENT_LENGTH ; 
 char* SVN_REPOS_DUMPFILE_TEXT_DELTA ; 
 int /*<<< orphan*/  SVN_STR_TO_REV (char const*) ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct revmap_t* apr_hash_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  output_revision (TYPE_1__*) ; 
 scalar_t__ skip_path (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  svn__atoui64 (char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 void* svn_hash_gets (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  svn_repos__dumpfile_header_push (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  svn_repos__dumpfile_header_pushf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_repos__dumpfile_headers_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
new_node_record(void **node_baton,
                apr_hash_t *headers,
                void *rev_baton,
                apr_pool_t *pool)
{
  struct parse_baton_t *pb;
  struct node_baton_t *nb;
  char *node_path, *copyfrom_path;
  apr_hash_index_t *hi;
  const char *tcl;

  *node_baton = apr_palloc(pool, sizeof(struct node_baton_t));
  nb          = *node_baton;
  nb->rb      = rev_baton;
  nb->node_pool = pool;
  pb          = nb->rb->pb;

  node_path = svn_hash_gets(headers, SVN_REPOS_DUMPFILE_NODE_PATH);
  copyfrom_path = svn_hash_gets(headers, SVN_REPOS_DUMPFILE_NODE_COPYFROM_PATH);

  /* Ensure that paths start with a leading '/'. */
  if (node_path[0] != '/')
    node_path = apr_pstrcat(pool, "/", node_path, SVN_VA_NULL);
  if (copyfrom_path && copyfrom_path[0] != '/')
    copyfrom_path = apr_pstrcat(pool, "/", copyfrom_path, SVN_VA_NULL);

  nb->do_skip = skip_path(node_path, pb->prefixes,
                          pb->do_exclude, pb->glob);

  /* If we're skipping the node, take note of path, discarding the
     rest.  */
  if (nb->do_skip)
    {
      svn_hash_sets(pb->dropped_nodes,
                    apr_pstrdup(apr_hash_pool_get(pb->dropped_nodes),
                                node_path),
                    (void *)1);
      nb->rb->had_dropped_nodes = TRUE;
    }
  else
    {
      const char *kind;
      const char *action;

      tcl = svn_hash_gets(headers, SVN_REPOS_DUMPFILE_TEXT_CONTENT_LENGTH);

      /* Test if this node was copied from dropped source. */
      if (copyfrom_path &&
          skip_path(copyfrom_path, pb->prefixes, pb->do_exclude, pb->glob))
        {
          /* This node was copied from a dropped source.
             We have a problem, since we did not want to drop this node too.

             However, there is one special case we'll handle.  If the node is
             a file, and this was a copy-and-modify operation, then the
             dumpfile should contain the new contents of the file.  In this
             scenario, we'll just do an add without history using the new
             contents.  */
          kind = svn_hash_gets(headers, SVN_REPOS_DUMPFILE_NODE_KIND);

          /* If there is a Text-content-length header, and the kind is
             "file", we just fallback to an add without history. */
          if (tcl && (strcmp(kind, "file") == 0))
            {
              svn_hash_sets(headers, SVN_REPOS_DUMPFILE_NODE_COPYFROM_PATH,
                            NULL);
              svn_hash_sets(headers, SVN_REPOS_DUMPFILE_NODE_COPYFROM_REV,
                            NULL);
              copyfrom_path = NULL;
            }
          /* Else, this is either a directory or a file whose contents we
             don't have readily available.  */
          else
            {
              return svn_error_createf
                (SVN_ERR_INCOMPLETE_DATA, 0,
                 _("Invalid copy source path '%s'"), copyfrom_path);
            }
        }

      nb->has_props = FALSE;
      nb->has_text = FALSE;
      nb->has_prop_delta = FALSE;
      nb->has_text_delta = FALSE;
      nb->writing_begun = FALSE;
      nb->tcl = tcl ? svn__atoui64(tcl) : 0;
      nb->headers = svn_repos__dumpfile_headers_create(pool);
      nb->props = svn_stringbuf_create_empty(pool);
      nb->node_path = apr_pstrdup(pool, node_path);

      /* Now we know for sure that we have a node that will not be
         skipped, flush the revision if it has not already been done. */
      nb->rb->has_nodes = TRUE;
      if (! nb->rb->writing_begun)
        SVN_ERR(output_revision(nb->rb));

      /* A node record is required to begin with 'Node-path', skip the
         leading '/' to match the form used by 'svnadmin dump'. */
      svn_repos__dumpfile_header_push(
        nb->headers, SVN_REPOS_DUMPFILE_NODE_PATH, node_path + 1);

      /* Node-kind is next and is optional. */
      kind = svn_hash_gets(headers, SVN_REPOS_DUMPFILE_NODE_KIND);
      if (kind)
        svn_repos__dumpfile_header_push(
          nb->headers, SVN_REPOS_DUMPFILE_NODE_KIND, kind);

      /* Node-action is next and required. */
      action = svn_hash_gets(headers, SVN_REPOS_DUMPFILE_NODE_ACTION);
      if (action)
        svn_repos__dumpfile_header_push(
          nb->headers, SVN_REPOS_DUMPFILE_NODE_ACTION, action);
      else
        return svn_error_createf(SVN_ERR_INCOMPLETE_DATA, 0,
                                 _("Missing Node-action for path '%s'"),
                                 node_path);

      for (hi = apr_hash_first(pool, headers); hi; hi = apr_hash_next(hi))
        {
          const char *key = apr_hash_this_key(hi);
          const char *val = apr_hash_this_val(hi);

          if ((!strcmp(key, SVN_REPOS_DUMPFILE_PROP_DELTA))
              && (!strcmp(val, "true")))
            nb->has_prop_delta = TRUE;

          if ((!strcmp(key, SVN_REPOS_DUMPFILE_TEXT_DELTA))
              && (!strcmp(val, "true")))
            nb->has_text_delta = TRUE;

          if ((!strcmp(key, SVN_REPOS_DUMPFILE_CONTENT_LENGTH))
              || (!strcmp(key, SVN_REPOS_DUMPFILE_PROP_CONTENT_LENGTH))
              || (!strcmp(key, SVN_REPOS_DUMPFILE_TEXT_CONTENT_LENGTH))
              || (!strcmp(key, SVN_REPOS_DUMPFILE_NODE_PATH))
              || (!strcmp(key, SVN_REPOS_DUMPFILE_NODE_KIND))
              || (!strcmp(key, SVN_REPOS_DUMPFILE_NODE_ACTION)))
            continue;

          /* Rewrite Node-Copyfrom-Rev if we are renumbering revisions.
             The number points to some revision in the past. We keep track
             of revision renumbering in an apr_hash, which maps original
             revisions to new ones. Dropped revision are mapped to -1.
             This should never happen here.
          */
          if (pb->do_renumber_revs
              && (!strcmp(key, SVN_REPOS_DUMPFILE_NODE_COPYFROM_REV)))
            {
              svn_revnum_t cf_orig_rev;
              struct revmap_t *cf_renum_val;

              cf_orig_rev = SVN_STR_TO_REV(val);
              cf_renum_val = apr_hash_get(pb->renumber_history,
                                          &cf_orig_rev,
                                          sizeof(cf_orig_rev));
              if (! (cf_renum_val && SVN_IS_VALID_REVNUM(cf_renum_val->rev)))
                return svn_error_createf
                  (SVN_ERR_NODE_UNEXPECTED_KIND, NULL,
                   _("No valid copyfrom revision in filtered stream"));
              svn_repos__dumpfile_header_pushf(
                nb->headers, SVN_REPOS_DUMPFILE_NODE_COPYFROM_REV,
                "%ld", cf_renum_val->rev);
              continue;
            }

          /* passthru: put header straight to output */
          svn_repos__dumpfile_header_push(nb->headers, key, val);
        }
    }

  return SVN_NO_ERROR;
}