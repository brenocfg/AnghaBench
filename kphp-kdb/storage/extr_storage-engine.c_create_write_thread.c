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
typedef  int /*<<< orphan*/  volume_t ;
struct gather_data {long long req_id; unsigned char* filedata; int filedata_len; int content_type; struct gather_data* prev; struct gather_data* next; int /*<<< orphan*/  q; int /*<<< orphan*/  writing_thread; void* filename; void* key; scalar_t__ key_len; int /*<<< orphan*/ * V; struct connection* c; } ;
struct connection {int /*<<< orphan*/  query_start_time; } ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 int /*<<< orphan*/  active_gathers ; 
 struct gather_data* active_write_threads ; 
 int /*<<< orphan*/  create_inbound_query (struct gather_data*,struct connection*,double) ; 
 int /*<<< orphan*/  free_gather (struct gather_data*) ; 
 int /*<<< orphan*/  mytime () ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_attr_setstacksize (int /*<<< orphan*/ *,int) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  rpc_create_inbound_query (struct gather_data*,struct connection*,double) ; 
 scalar_t__ rpc_mode (struct gather_data*) ; 
 int /*<<< orphan*/  strcpy (void*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (struct gather_data*,struct connection*,double) ; 
 void* tszmalloc (scalar_t__) ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 
 int /*<<< orphan*/  write_thread ; 
 struct gather_data* zmalloc0 (int) ; 

int create_write_thread (struct connection *c, long long req_id, volume_t *V, const char *key, const char *filename, unsigned char *filedata, int filedata_len, int content_type) {
  pthread_attr_t attr;
  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
  pthread_attr_setstacksize (&attr, 4 << 20);
  active_gathers++;
  struct gather_data *A = zmalloc0 (sizeof (struct gather_data));

  A->req_id = req_id;
  A->c = c;
  A->V = V;
  A->key_len = strlen (key);
  A->key = tszmalloc (A->key_len + 1);
  strcpy (A->key, key);
  if (filename) {
    A->filename = tszmalloc (strlen (filename) + 1);
    strcpy (A->filename, filename);
  }

  A->filedata = filedata;
  A->filedata_len = filedata_len;
  A->content_type = content_type;

  int r = pthread_create (&A->writing_thread, &attr, write_thread, (void *) A);

  if (r) {
    vkprintf (1, "create_write_thread: pthread_create failed. %m\n");
    pthread_attr_destroy (&attr);
    free_gather (A);
    return -1;
  }

  pthread_attr_destroy (&attr);

  c->query_start_time = mytime ();

  A->q = (rpc_mode (A) ? rpc_create_inbound_query : create_inbound_query) (A, c, 600.0);

  A->next = active_write_threads;
  if (active_write_threads) {
    active_write_threads->prev = A;
  }
  active_write_threads = A;
  return 0;
}