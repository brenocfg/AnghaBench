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
typedef  int /*<<< orphan*/  svn_error_t ;
struct write_svndiff_strings_baton {int header_read; char version; int size; int /*<<< orphan*/ * key; TYPE_1__* trail; int /*<<< orphan*/  fs; } ;
typedef  int apr_size_t ;
struct TYPE_2__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_GENERAL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__string_append (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
write_svndiff_strings(void *baton, const char *data, apr_size_t *len)
{
  struct write_svndiff_strings_baton *wb = baton;
  const char *buf = data;
  apr_size_t nheader = 0;

  /* If we haven't stripped all the header information from this
     stream yet, keep stripping.  If someone sends a first window
     through here that's shorter than 4 bytes long, this will probably
     cause a nuclear reactor meltdown somewhere in the American
     midwest.  */
  if (wb->header_read < 4)
    {
      nheader = 4 - wb->header_read;
      *len -= nheader;
      buf += nheader;
      wb->header_read += nheader;

      /* If we have *now* read the full 4-byte header, check that
         least byte for the version number of the svndiff format. */
      if (wb->header_read == 4)
        wb->version = *(buf - 1);
    }

  /* Append to the current string we're writing (or create a new one
     if WB->key is NULL). */
  SVN_ERR(svn_fs_bdb__string_append(wb->fs, &(wb->key), *len,
                                    buf, wb->trail, wb->trail->pool));

  /* Make sure we (still) have a key. */
  if (wb->key == NULL)
    return svn_error_create(SVN_ERR_FS_GENERAL, NULL,
                            _("Failed to get new string key"));

  /* Restore *LEN to the value it *would* have been were it not for
     header stripping. */
  *len += nheader;

  /* Increment our running total of bytes written to this string. */
  wb->size += *len;

  return SVN_NO_ERROR;
}