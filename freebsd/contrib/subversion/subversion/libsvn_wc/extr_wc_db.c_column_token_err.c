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
struct TYPE_4__ {int val; } ;
typedef  TYPE_1__ svn_token_map_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_WC_CORRUPT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_token__from_word_err (int*,TYPE_1__ const*,char const*) ; 

__attribute__((used)) static int
column_token_err(svn_error_t **err,
                 svn_sqlite__stmt_t *stmt,
                 int column,
                 const svn_token_map_t *map)
{
  svn_error_t *err2;
  const char *word = svn_sqlite__column_text(stmt, column, NULL);
  int value;

  /* svn_token__from_word_err() handles NULL for us */
  err2 = svn_token__from_word_err(&value, map, word);

  if (err2)
    {
      *err = svn_error_compose_create(
                *err,
                svn_error_createf(
                    SVN_ERR_WC_CORRUPT, err2,
                    _("Encountered invalid node state in column %d of "
                      "info query to working copy database"),
                    column));
      value = map[0].val;
    }

  return value;
}