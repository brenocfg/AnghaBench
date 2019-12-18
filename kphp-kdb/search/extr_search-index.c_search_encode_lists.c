#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct search_index_hapax_legomena {int dummy; } ;
typedef  scalar_t__ hash_t ;
struct TYPE_12__ {int words; int hapax_legomena; int /*<<< orphan*/ * compression_bytes; } ;
struct TYPE_11__ {unsigned int doc_id_and_priority; scalar_t__ word; } ;
struct TYPE_10__ {scalar_t__ word; } ;
struct TYPE_9__ {scalar_t__ word; unsigned int doc_id; } ;

/* Variables and functions */
 TYPE_3__* HL ; 
 TYPE_7__ Header ; 
 TYPE_1__* P ; 
 int PC ; 
 TYPE_2__* W ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  encode_lists_reset () ; 
 int /*<<< orphan*/ * encoded_bytes ; 
 scalar_t__ in_title (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  search_encode_list (TYPE_1__*,int,TYPE_2__*,int const*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int) ; 

__attribute__((used)) static int search_encode_lists (const int methods[2], int quiet) {
  encode_lists_reset ();
  int i = 0, j, k, hl = 0;
  for (k = 0; k < PC; k = j) {
    hash_t word = P[k].word;
    for (j = k + 1; j < PC && P[j].word == word; j++) {}
    if (j - k > 1) {
      assert (i < Header.words);
      W[i].word = word;
      search_encode_list (P+k, j-k, W+i, methods, quiet);
      i++;
    } else {
      if (hl >= Header.hapax_legomena) { vkprintf (1, "h1 = %d, Header.hapax_legomena = %d\n", hl, Header.hapax_legomena); }
      assert (hl < Header.hapax_legomena);
      HL[hl].word = word;
      HL[hl].doc_id_and_priority = P[k].doc_id;
      if (in_title (P + k)) {
        HL[hl].doc_id_and_priority |= (1U << 31);
      }
      hl++;
    }
  }
  assert (i == Header.words);
  assert (hl == Header.hapax_legomena);
  memset (HL+hl, 0, sizeof (struct search_index_hapax_legomena));
  for (k=0;k<2;k++) {
    Header.compression_bytes[2*methods[k]+k] = encoded_bytes[k];
  }
  return i;
}