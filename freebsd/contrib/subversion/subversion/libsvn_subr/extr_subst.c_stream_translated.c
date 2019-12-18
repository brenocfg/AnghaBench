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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct translated_stream_baton {void* buf; void* iterpool; scalar_t__ readbuf_off; int /*<<< orphan*/  readbuf; int /*<<< orphan*/  written; void* out_baton; void* in_baton; int /*<<< orphan*/ * stream; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SVN__TRANSLATION_BUF_SIZE ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,void**) ; 
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,void const*) ; 
 void* create_translation_baton (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 void* svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_create (struct translated_stream_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_stream_supports_mark (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_dup (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  translated_stream_close ; 
 int /*<<< orphan*/  translated_stream_mark ; 
 int /*<<< orphan*/  translated_stream_read ; 
 int /*<<< orphan*/  translated_stream_seek ; 
 int /*<<< orphan*/  translated_stream_write ; 

__attribute__((used)) static svn_stream_t *
stream_translated(svn_stream_t *stream,
                  const char *eol_str,
                  svn_boolean_t *translated_eol,
                  svn_boolean_t repair,
                  apr_hash_t *keywords,
                  svn_boolean_t expand,
                  apr_pool_t *result_pool)
{
  struct translated_stream_baton *baton
    = apr_palloc(result_pool, sizeof(*baton));
  svn_stream_t *s = svn_stream_create(baton, result_pool);

  /* Make sure EOL_STR and KEYWORDS are allocated in RESULT_POOL
     so they have the same lifetime as the stream. */
  if (eol_str)
    eol_str = apr_pstrdup(result_pool, eol_str);
  if (keywords)
    {
      if (apr_hash_count(keywords) == 0)
        keywords = NULL;
      else
        {
          /* deep copy the hash to make sure it's allocated in RESULT_POOL */
          apr_hash_t *copy = apr_hash_make(result_pool);
          apr_hash_index_t *hi;
          apr_pool_t *subpool;

          subpool = svn_pool_create(result_pool);
          for (hi = apr_hash_first(subpool, keywords);
               hi; hi = apr_hash_next(hi))
            {
              const void *key;
              void *val;

              apr_hash_this(hi, &key, NULL, &val);
              svn_hash_sets(copy, apr_pstrdup(result_pool, key),
                            svn_string_dup(val, result_pool));
            }
          svn_pool_destroy(subpool);

          keywords = copy;
        }
    }

  /* Setup the baton fields */
  baton->stream = stream;
  baton->in_baton
    = create_translation_baton(eol_str, translated_eol, repair, keywords,
                               expand, result_pool);
  baton->out_baton
    = create_translation_baton(eol_str, translated_eol, repair, keywords,
                               expand, result_pool);
  baton->written = FALSE;
  baton->readbuf = svn_stringbuf_create_empty(result_pool);
  baton->readbuf_off = 0;
  baton->iterpool = svn_pool_create(result_pool);
  baton->buf = apr_palloc(result_pool, SVN__TRANSLATION_BUF_SIZE);

  /* Setup the stream methods */
  svn_stream_set_read2(s, NULL /* only full read support */,
                       translated_stream_read);
  svn_stream_set_write(s, translated_stream_write);
  svn_stream_set_close(s, translated_stream_close);
  if (svn_stream_supports_mark(stream))
    {
      svn_stream_set_mark(s, translated_stream_mark);
      svn_stream_set_seek(s, translated_stream_seek);
    }

  return s;
}