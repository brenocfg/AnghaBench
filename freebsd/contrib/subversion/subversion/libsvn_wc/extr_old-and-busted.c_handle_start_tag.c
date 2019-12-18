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
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ svn_wc_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct entries_accumulator {int /*<<< orphan*/  entries; int /*<<< orphan*/  parser; int /*<<< orphan*/  pool; int /*<<< orphan*/  scratch_pool; } ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRIES_TAG_ENTRY ; 
 int /*<<< orphan*/ * atts_to_entry (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_xml_make_att_hash (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_xml_signal_bailout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_start_tag(void *userData, const char *tagname, const char **atts)
{
  struct entries_accumulator *accum = userData;
  apr_hash_t *attributes;
  svn_wc_entry_t *entry;
  svn_error_t *err;

  /* We only care about the `entry' tag; all other tags, such as `xml'
     and `wc-entries', are ignored. */
  if (strcmp(tagname, ENTRIES_TAG_ENTRY))
    return;

  svn_pool_clear(accum->scratch_pool);
  /* Make an entry from the attributes. */
  attributes = svn_xml_make_att_hash(atts, accum->scratch_pool);
  err = atts_to_entry(&entry, attributes, accum->pool);
  if (err)
    {
      svn_xml_signal_bailout(err, accum->parser);
      return;
    }

  /* Find the name and set up the entry under that name.  This
     should *NOT* be NULL, since svn_wc__atts_to_entry() should
     have made it into SVN_WC_ENTRY_THIS_DIR. */
  svn_hash_sets(accum->entries, entry->name, entry);
}