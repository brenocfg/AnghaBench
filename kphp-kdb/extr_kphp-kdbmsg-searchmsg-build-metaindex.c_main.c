#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  userlist_entry_t ;
struct TYPE_6__ {scalar_t__ magic; int hash_cnt; int list_cnt; scalar_t__ user_id; } ;
typedef  TYPE_1__ user_header_t ;
struct TYPE_7__ {int hash_cnt; int list_cnt; scalar_t__ offset; scalar_t__ file_no; scalar_t__ user_id; } ;

/* Variables and functions */
 TYPE_2__* A ; 
 TYPE_2__* B ; 
 scalar_t__ MAIL_INDEX_BLOCK_MAGIC ; 
 size_t MAX_USERS ; 
 size_t N ; 
 int /*<<< orphan*/  O_RDONLY ; 
 TYPE_2__** P ; 
 int /*<<< orphan*/  READ_AHEAD ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * buff ; 
 scalar_t__ cur_offs ; 
 scalar_t__ ifd ; 
 scalar_t__ load_offs ; 
 scalar_t__ lseek (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_sort (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ open (char const*,int /*<<< orphan*/ ) ; 
 int r ; 
 int read (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int write (int,TYPE_2__*,size_t) ; 

int main (int argc, const char *argv[]) {
  user_header_t *UH;
  int i;
  assert (argc == 2);
  ifd = open (argv[1], O_RDONLY);
  assert (ifd >= 0);
  N = 0;
  do {
    if (cur_offs + sizeof(user_header_t) > load_offs + r) {
      assert (lseek (ifd, cur_offs, SEEK_SET) == cur_offs);
      r = read (ifd, buff, READ_AHEAD);
      assert (r >= 0);
      load_offs = cur_offs;
      // fprintf (stderr, "%d bytes read at position %lld, [0]=%02x\n", r, cur_offs, buff[0]);
      if (!r) break;
      assert (r >= sizeof(user_header_t));
    }
    //fprintf (stderr, "cur_offs = %lld\n", cur_offs);
    UH = (user_header_t *) &buff[cur_offs - load_offs];
    //fprintf (stderr, "magic = %08lx\n", UH->magic);
    assert (UH->magic == MAIL_INDEX_BLOCK_MAGIC);
    //fprintf (stderr, "user %ld, hash_cnt=%ld, list_cnt=%ld, pos=%lld\n", UH->user_id, UH->hash_cnt, UH->list_cnt, cur_offs);
    assert ((unsigned long) UH->user_id < (1L << 31) && (unsigned long) UH->hash_cnt < (1L << 24) && (unsigned long) UH->list_cnt < (1L << 26));
    cur_offs += sizeof (user_header_t);
    if (UH->user_id && (unsigned long) UH->user_id < (1L << 26)) {
      A[N].user_id = UH->user_id;
      A[N].hash_cnt = UH->hash_cnt;
      A[N].list_cnt = UH->list_cnt;
      A[N].file_no = 0;
      A[N].offset = cur_offs;
      P[N] = &A[N];
      N++;
    }
    cur_offs += UH->hash_cnt * 16 + UH->list_cnt * 4;
    assert (N <= MAX_USERS);
  } while (1);
  my_sort (0, N-1);
  for (i = 0; i < N; i++) B[i] = *P[i];
  i = write (1, B, N * sizeof(userlist_entry_t));
  assert (i == N * sizeof(userlist_entry_t));
  return 0;
}