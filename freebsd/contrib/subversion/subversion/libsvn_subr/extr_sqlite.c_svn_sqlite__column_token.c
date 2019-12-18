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
typedef  int /*<<< orphan*/  svn_token_map_t ;
struct TYPE_3__ {int /*<<< orphan*/  s3stmt; } ;
typedef  TYPE_1__ svn_sqlite__stmt_t ;

/* Variables and functions */
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ ,int) ; 
 int svn_token__from_word_strict (int /*<<< orphan*/  const*,char const*) ; 

int
svn_sqlite__column_token(svn_sqlite__stmt_t *stmt,
                         int column,
                         const svn_token_map_t *map)
{
  /* cast from 'unsigned char' to regular 'char'  */
  const char *word = (const char *)sqlite3_column_text(stmt->s3stmt, column);

  return svn_token__from_word_strict(map, word);
}