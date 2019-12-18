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
struct sched_param {int sched_priority; } ;
struct device {int dummy; } ;
struct crypto_engine {int rt; int running; int busy; int idling; int cur_req_prepared; TYPE_1__* kworker; int /*<<< orphan*/  pump_requests; int /*<<< orphan*/  name; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; struct device* priv_data; struct device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ENGINE_MAX_QLEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int MAX_RT_PRIO ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  crypto_init_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_pump_work ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 char* dev_name (struct device*) ; 
 struct crypto_engine* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* kthread_create_worker (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_setscheduler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct crypto_engine *crypto_engine_alloc_init(struct device *dev, bool rt)
{
	struct sched_param param = { .sched_priority = MAX_RT_PRIO / 2 };
	struct crypto_engine *engine;

	if (!dev)
		return NULL;

	engine = devm_kzalloc(dev, sizeof(*engine), GFP_KERNEL);
	if (!engine)
		return NULL;

	engine->dev = dev;
	engine->rt = rt;
	engine->running = false;
	engine->busy = false;
	engine->idling = false;
	engine->cur_req_prepared = false;
	engine->priv_data = dev;
	snprintf(engine->name, sizeof(engine->name),
		 "%s-engine", dev_name(dev));

	crypto_init_queue(&engine->queue, CRYPTO_ENGINE_MAX_QLEN);
	spin_lock_init(&engine->queue_lock);

	engine->kworker = kthread_create_worker(0, "%s", engine->name);
	if (IS_ERR(engine->kworker)) {
		dev_err(dev, "failed to create crypto request pump task\n");
		return NULL;
	}
	kthread_init_work(&engine->pump_requests, crypto_pump_work);

	if (engine->rt) {
		dev_info(dev, "will run requests pump with realtime priority\n");
		sched_setscheduler(engine->kworker->task, SCHED_FIFO, &param);
	}

	return engine;
}