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
typedef  void* svn_boolean_t ;
struct translation_baton {char const* eol_str; void** translated_eol; void** interesting; int /*<<< orphan*/  nl_translation_skippable; scalar_t__ src_format_len; scalar_t__ keyword_off; scalar_t__ newline_off; void* expand; int /*<<< orphan*/ * keywords; void* repair; int /*<<< orphan*/  eol_str_len; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* TRUE ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 struct translation_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  svn_tristate_unknown ; 

__attribute__((used)) static struct translation_baton *
create_translation_baton(const char *eol_str,
                         svn_boolean_t *translated_eol,
                         svn_boolean_t repair,
                         apr_hash_t *keywords,
                         svn_boolean_t expand,
                         apr_pool_t *pool)
{
  struct translation_baton *b = apr_palloc(pool, sizeof(*b));

  /* For efficiency, convert an empty set of keywords to NULL. */
  if (keywords && (apr_hash_count(keywords) == 0))
    keywords = NULL;

  b->eol_str = eol_str;
  b->eol_str_len = eol_str ? strlen(eol_str) : 0;
  b->translated_eol = translated_eol;
  b->repair = repair;
  b->keywords = keywords;
  b->expand = expand;
  b->newline_off = 0;
  b->keyword_off = 0;
  b->src_format_len = 0;
  b->nl_translation_skippable = svn_tristate_unknown;

  /* Most characters don't start translation actions.
   * Mark those that do depending on the parameters we got. */
  memset(b->interesting, FALSE, sizeof(b->interesting));
  if (keywords)
    b->interesting['$'] = TRUE;
  if (eol_str)
    {
      b->interesting['\r'] = TRUE;
      b->interesting['\n'] = TRUE;
    }

  return b;
}