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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  compression_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SVN_DELTA_COMPRESSION_LEVEL_DEFAULT ; 
 int SVN_DELTA_COMPRESSION_LEVEL_NONE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_CONFIG_VALUE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  compression_type_lz4 ; 
 int /*<<< orphan*/  compression_type_none ; 
 int /*<<< orphan*/  compression_type_zlib ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  svn_cstring_atoi (int*,char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static svn_error_t *
parse_compression_option(compression_type_t *compression_type_p,
                         int *compression_level_p,
                         const char *value)
{
  compression_type_t type;
  int level;
  svn_boolean_t is_valid = TRUE;

  /* compression = none | lz4 | zlib | zlib-1 ... zlib-9 */
  if (strcmp(value, "none") == 0)
    {
      type = compression_type_none;
      level = SVN_DELTA_COMPRESSION_LEVEL_NONE;
    }
  else if (strcmp(value, "lz4") == 0)
    {
      type = compression_type_lz4;
      level = SVN_DELTA_COMPRESSION_LEVEL_DEFAULT;
    }
  else if (strncmp(value, "zlib", 4) == 0)
    {
      const char *p = value + 4;

      type = compression_type_zlib;
      if (*p == 0)
        {
          level = SVN_DELTA_COMPRESSION_LEVEL_DEFAULT;
        }
      else if (*p == '-')
        {
          p++;
          SVN_ERR(svn_cstring_atoi(&level, p));
          if (level < 1 || level > 9)
            is_valid = FALSE;
        }
      else
        is_valid = FALSE;
    }
  else
    {
      is_valid = FALSE;
    }

  if (!is_valid)
    return svn_error_createf(SVN_ERR_BAD_CONFIG_VALUE, NULL,
                           _("Invalid 'compression' value '%s' in the config"),
                             value);

  *compression_type_p = type;
  *compression_level_p = level;
  return SVN_NO_ERROR;
}