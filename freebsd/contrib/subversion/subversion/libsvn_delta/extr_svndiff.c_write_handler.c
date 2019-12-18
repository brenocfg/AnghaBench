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
typedef  int /*<<< orphan*/  svn_txdelta_window_t ;
typedef  scalar_t__ svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct decode_baton {scalar_t__ header_bytes; int version; scalar_t__ window_header_len; scalar_t__ last_sview_offset; scalar_t__ last_sview_len; scalar_t__ sview_offset; scalar_t__ sview_len; scalar_t__ inslen; scalar_t__ newlen; TYPE_1__* buffer; int /*<<< orphan*/  subpool; int /*<<< orphan*/  consumer_baton; int /*<<< orphan*/  (* consumer_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;scalar_t__ tview_len; } ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_3__ {int len; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ MAX_INSTRUCTION_SECTION_LEN ; 
 scalar_t__ SVNDIFF_HEADER_SIZE ; 
 scalar_t__ SVNDIFF_V0 ; 
 scalar_t__ SVNDIFF_V1 ; 
 scalar_t__ SVNDIFF_V2 ; 
 scalar_t__ SVN_DELTA_WINDOW_SIZE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_SVNDIFF_BACKWARD_VIEW ; 
 int /*<<< orphan*/  SVN_ERR_SVNDIFF_CORRUPT_WINDOW ; 
 int /*<<< orphan*/  SVN_ERR_SVNDIFF_INVALID_HEADER ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int SVN__MAX_ENCODED_UINT_LEN ; 
 int /*<<< orphan*/  _ (char*) ; 
 unsigned char* decode_file_offset (scalar_t__*,unsigned char const*,unsigned char const*) ; 
 unsigned char* decode_size (scalar_t__*,unsigned char const*,unsigned char const*) ; 
 int /*<<< orphan*/  decode_window (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,unsigned char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ memcmp (char const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (TYPE_1__*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  svn_stringbuf_remove (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static svn_error_t *
write_handler(void *baton,
              const char *buffer,
              apr_size_t *len)
{
  struct decode_baton *db = (struct decode_baton *) baton;
  const unsigned char *p, *end;
  apr_size_t buflen = *len;

  /* Chew up four bytes at the beginning for the header.  */
  if (db->header_bytes < SVNDIFF_HEADER_SIZE)
    {
      apr_size_t nheader = SVNDIFF_HEADER_SIZE - db->header_bytes;
      if (nheader > buflen)
        nheader = buflen;
      if (memcmp(buffer, SVNDIFF_V0 + db->header_bytes, nheader) == 0)
        db->version = 0;
      else if (memcmp(buffer, SVNDIFF_V1 + db->header_bytes, nheader) == 0)
        db->version = 1;
      else if (memcmp(buffer, SVNDIFF_V2 + db->header_bytes, nheader) == 0)
        db->version = 2;
      else
        return svn_error_create(SVN_ERR_SVNDIFF_INVALID_HEADER, NULL,
                                _("Svndiff has invalid header"));
      buflen -= nheader;
      buffer += nheader;
      db->header_bytes += nheader;
    }

  /* Concatenate the old with the new.  */
  svn_stringbuf_appendbytes(db->buffer, buffer, buflen);

  /* We have a buffer of svndiff data that might be good for:

     a) an integral number of windows' worth of data - this is a
        trivial case.  Make windows from our data and ship them off.

     b) a non-integral number of windows' worth of data - we shall
        consume the integral portion of the window data, and then
        somewhere in the following loop the decoding of the svndiff
        data will run out of stuff to decode, and will simply return
        SVN_NO_ERROR, anxiously awaiting more data.
  */

  while (1)
    {
      svn_txdelta_window_t window;

      /* Read the header, if we have enough bytes for that.  */
      p = (const unsigned char *) db->buffer->data;
      end = (const unsigned char *) db->buffer->data + db->buffer->len;

      if (db->window_header_len == 0)
        {
          svn_filesize_t sview_offset;
          apr_size_t sview_len, tview_len, inslen, newlen;
          const unsigned char *hdr_start = p;

          p = decode_file_offset(&sview_offset, p, end);
          if (p == NULL)
              break;

          p = decode_size(&sview_len, p, end);
          if (p == NULL)
              break;

          p = decode_size(&tview_len, p, end);
          if (p == NULL)
              break;

          p = decode_size(&inslen, p, end);
          if (p == NULL)
              break;

          p = decode_size(&newlen, p, end);
          if (p == NULL)
              break;

          if (tview_len > SVN_DELTA_WINDOW_SIZE ||
              sview_len > SVN_DELTA_WINDOW_SIZE ||
              /* for svndiff1, newlen includes the original length */
              newlen > SVN_DELTA_WINDOW_SIZE + SVN__MAX_ENCODED_UINT_LEN ||
              inslen > MAX_INSTRUCTION_SECTION_LEN)
            return svn_error_create(
                     SVN_ERR_SVNDIFF_CORRUPT_WINDOW, NULL,
                     _("Svndiff contains a too-large window"));

          /* Check for integer overflow.  */
          if (sview_offset < 0 || inslen + newlen < inslen
              || sview_len + tview_len < sview_len
              || (apr_size_t)sview_offset + sview_len < (apr_size_t)sview_offset)
            return svn_error_create(
                      SVN_ERR_SVNDIFF_CORRUPT_WINDOW, NULL,
                      _("Svndiff contains corrupt window header"));

          /* Check for source windows which slide backwards.  */
          if (sview_len > 0
              && (sview_offset < db->last_sview_offset
                  || (sview_offset + sview_len
                      < db->last_sview_offset + db->last_sview_len)))
            return svn_error_create(
                     SVN_ERR_SVNDIFF_BACKWARD_VIEW, NULL,
                     _("Svndiff has backwards-sliding source views"));

          /* Remember parsed window header. */
          db->window_header_len = p - hdr_start;
          db->sview_offset = sview_offset;
          db->sview_len = sview_len;
          db->tview_len = tview_len;
          db->inslen = inslen;
          db->newlen = newlen;
        }
      else
        {
          /* Skip already parsed window header. */
          p += db->window_header_len;
        }

      /* Wait for more data if we don't have enough bytes for the
         whole window. */
      if ((apr_size_t) (end - p) < db->inslen + db->newlen)
        return SVN_NO_ERROR;

      /* Decode the window and send it off. */
      SVN_ERR(decode_window(&window, db->sview_offset, db->sview_len,
                            db->tview_len, db->inslen, db->newlen, p,
                            db->subpool, db->version));
      SVN_ERR(db->consumer_func(&window, db->consumer_baton));

      p += db->inslen + db->newlen;

      /* Remove processed data from the buffer.  */
      svn_stringbuf_remove(db->buffer, 0, db->buffer->len - (end - p));

      /* Reset window header length. */
      db->window_header_len = 0;

      /* Remember the offset and length of the source view for next time.  */
      db->last_sview_offset = db->sview_offset;
      db->last_sview_len = db->sview_len;

      /* Clear subpool. */
      svn_pool_clear(db->subpool);
    }

  /* At this point we processed all integral windows and DB->BUFFER is empty
     or contains partially read window header.
     Check that unprocessed data is not larger than theoretical maximum
     window header size. */
  if (db->buffer->len > 5 * SVN__MAX_ENCODED_UINT_LEN)
    return svn_error_create(SVN_ERR_SVNDIFF_CORRUPT_WINDOW, NULL,
                            _("Svndiff contains a too-large window header"));

  return SVN_NO_ERROR;
}