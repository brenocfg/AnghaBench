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
struct sockaddr {int dummy; } ;
struct rping_cb {int server; int size; int count; int cm_id; int /*<<< orphan*/  cm_channel; int /*<<< orphan*/  cmthread; int /*<<< orphan*/  validate; int /*<<< orphan*/  verbose; void* port; int /*<<< orphan*/  ssource; int /*<<< orphan*/  sin; int /*<<< orphan*/  sem; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOG (char*,...) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IDLE ; 
 int /*<<< orphan*/  RDMA_PS_TCP ; 
 int /*<<< orphan*/  RPING_BUFSIZE ; 
 int RPING_MIN_BUFSIZE ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  cm_thread ; 
 int /*<<< orphan*/  debug ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  free (struct rping_cb*) ; 
 int get_addr (char*,struct sockaddr*) ; 
 int getopt (int,char**,char*) ; 
 void* htobe16 (int) ; 
 struct rping_cb* malloc (int) ; 
 int /*<<< orphan*/  memset (struct rping_cb*,int /*<<< orphan*/ ,int) ; 
 char* optarg ; 
 scalar_t__ opterr ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rping_cb*) ; 
 int /*<<< orphan*/  rdma_create_event_channel () ; 
 int rdma_create_id (int /*<<< orphan*/ ,int*,struct rping_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_event_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_id (int) ; 
 int rping_run_client (struct rping_cb*) ; 
 int rping_run_persistent_server (struct rping_cb*) ; 
 int rping_run_server (struct rping_cb*) ; 
 int /*<<< orphan*/  sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char *argv[])
{
	struct rping_cb *cb;
	int op;
	int ret = 0;
	int persistent_server = 0;

	cb = malloc(sizeof(*cb));
	if (!cb)
		return -ENOMEM;

	memset(cb, 0, sizeof(*cb));
	cb->server = -1;
	cb->state = IDLE;
	cb->size = 64;
	cb->port = htobe16(7174);
	sem_init(&cb->sem, 0, 0);

	/* initialize sockaddr structure with defaults */
	ret = get_addr("0.0.0.0", (struct sockaddr *) &cb->sin);
	if (ret)
		goto out;

	opterr = 0;
	while ((op=getopt(argc, argv, "a:I:Pp:C:S:t:scvVd")) != -1) {
		switch (op) {
		case 'a':
			ret = get_addr(optarg, (struct sockaddr *) &cb->sin);
			break;
		case 'I':
			ret = get_addr(optarg, (struct sockaddr *) &cb->ssource);
			break;
		case 'P':
			persistent_server = 1;
			break;
		case 'p':
			cb->port = htobe16(atoi(optarg));
			DEBUG_LOG("port %d\n", (int) atoi(optarg));
			break;
		case 's':
			cb->server = 1;
			DEBUG_LOG("server\n");
			break;
		case 'c':
			cb->server = 0;
			DEBUG_LOG("client\n");
			break;
		case 'S':
			cb->size = atoi(optarg);
			if ((cb->size < RPING_MIN_BUFSIZE) ||
			    (cb->size > (RPING_BUFSIZE - 1))) {
				fprintf(stderr, "Invalid size %d "
				       "(valid range is %zd to %d)\n",
				       cb->size, RPING_MIN_BUFSIZE, RPING_BUFSIZE);
				ret = EINVAL;
			} else
				DEBUG_LOG("size %d\n", (int) atoi(optarg));
			break;
		case 'C':
			cb->count = atoi(optarg);
			if (cb->count < 0) {
				fprintf(stderr, "Invalid count %d\n",
					cb->count);
				ret = EINVAL;
			} else
				DEBUG_LOG("count %d\n", (int) cb->count);
			break;
		case 'v':
			cb->verbose++;
			DEBUG_LOG("verbose\n");
			break;
		case 'V':
			cb->validate++;
			DEBUG_LOG("validate data\n");
			break;
		case 'd':
			debug++;
			break;
		default:
			usage("rping");
			ret = EINVAL;
			goto out;
		}
	}
	if (ret)
		goto out;

	if (cb->server == -1) {
		usage("rping");
		ret = EINVAL;
		goto out;
	}

	cb->cm_channel = rdma_create_event_channel();
	if (!cb->cm_channel) {
		perror("rdma_create_event_channel");
		ret = errno;
		goto out;
	}

	ret = rdma_create_id(cb->cm_channel, &cb->cm_id, cb, RDMA_PS_TCP);
	if (ret) {
		perror("rdma_create_id");
		goto out2;
	}
	DEBUG_LOG("created cm_id %p\n", cb->cm_id);

	ret = pthread_create(&cb->cmthread, NULL, cm_thread, cb);
	if (ret) {
		perror("pthread_create");
		goto out2;
	}

	if (cb->server) {
		if (persistent_server)
			ret = rping_run_persistent_server(cb);
		else
			ret = rping_run_server(cb);
	} else {
		ret = rping_run_client(cb);
	}

	DEBUG_LOG("destroy cm_id %p\n", cb->cm_id);
	rdma_destroy_id(cb->cm_id);
out2:
	rdma_destroy_event_channel(cb->cm_channel);
out:
	free(cb);
	return ret;
}