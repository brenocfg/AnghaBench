#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
struct spacc_engine {int fifo_sz; int num_algs; int num_aeads; int stat_irq_thresh; scalar_t__ clk; int /*<<< orphan*/  packet_timeout; TYPE_2__* aeads; TYPE_4__* dev; int /*<<< orphan*/  registered_aeads; TYPE_3__* algs; int /*<<< orphan*/  registered_algs; int /*<<< orphan*/  complete; scalar_t__ in_flight; int /*<<< orphan*/  in_progress; int /*<<< orphan*/  completed; int /*<<< orphan*/  pending; scalar_t__ regs; int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  req_pool; int /*<<< orphan*/  name; scalar_t__ hash_key_base; scalar_t__ cipher_ctx_base; int /*<<< orphan*/  hash_pg_sz; int /*<<< orphan*/  cipher_pg_sz; int /*<<< orphan*/  max_ctxs; } ;
struct spacc_ddt {int dummy; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_21__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  cra_name; } ;
struct TYPE_20__ {TYPE_13__ alg; int /*<<< orphan*/  entry; struct spacc_engine* engine; } ;
struct TYPE_18__ {int /*<<< orphan*/  cra_name; } ;
struct TYPE_17__ {TYPE_1__ base; } ;
struct TYPE_19__ {TYPE_14__ alg; int /*<<< orphan*/  entry; struct spacc_engine* engine; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int MAX_DDT_LEN ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  SPACC_CRYPTO_IPSEC_CIPHER_PG_SZ ; 
 int SPACC_CRYPTO_IPSEC_FIFO_SZ ; 
 int /*<<< orphan*/  SPACC_CRYPTO_IPSEC_HASH_PG_SZ ; 
 int /*<<< orphan*/  SPACC_CRYPTO_IPSEC_MAX_CTXS ; 
 int /*<<< orphan*/  SPACC_CRYPTO_L2_CIPHER_PG_SZ ; 
 int SPACC_CRYPTO_L2_FIFO_SZ ; 
 int /*<<< orphan*/  SPACC_CRYPTO_L2_HASH_PG_SZ ; 
 int /*<<< orphan*/  SPACC_CRYPTO_L2_MAX_CTXS ; 
 scalar_t__ SPA_CIPH_KEY_BASE_REG_OFFSET ; 
 scalar_t__ SPA_HASH_KEY_BASE_REG_OFFSET ; 
 scalar_t__ SPA_IRQ_CTRL_REG_OFFSET ; 
 int SPA_IRQ_CTRL_STAT_CNT_OFFSET ; 
 int SPA_IRQ_EN_GLBL_EN ; 
 scalar_t__ SPA_IRQ_EN_REG_OFFSET ; 
 int SPA_IRQ_EN_STAT_EN ; 
 int /*<<< orphan*/  SZ_64K ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 scalar_t__ clk_get (TYPE_4__*,char*) ; 
 scalar_t__ clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  clk_put (scalar_t__) ; 
 int crypto_register_aead (TYPE_14__*) ; 
 int crypto_register_alg (TYPE_13__*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_stat_irq_thresh ; 
 int /*<<< orphan*/  dev_dbg (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 int device_create_file (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (TYPE_4__*,int /*<<< orphan*/ *) ; 
 struct spacc_engine* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_request_irq (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spacc_engine*) ; 
 int /*<<< orphan*/  dmam_pool_create (int /*<<< orphan*/ ,TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 
 void* ipsec_engine_aeads ; 
 void* ipsec_engine_algs ; 
 void* l2_engine_algs ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spacc_engine*) ; 
 int /*<<< orphan*/  spacc_packet_timeout ; 
 int /*<<< orphan*/  spacc_spacc_complete ; 
 int /*<<< orphan*/  spacc_spacc_irq ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int spacc_probe(struct platform_device *pdev)
{
	int i, err, ret;
	struct resource *irq;
	struct device_node *np = pdev->dev.of_node;
	struct spacc_engine *engine = devm_kzalloc(&pdev->dev, sizeof(*engine),
						   GFP_KERNEL);
	if (!engine)
		return -ENOMEM;

	if (of_device_is_compatible(np, "picochip,spacc-ipsec")) {
		engine->max_ctxs	= SPACC_CRYPTO_IPSEC_MAX_CTXS;
		engine->cipher_pg_sz	= SPACC_CRYPTO_IPSEC_CIPHER_PG_SZ;
		engine->hash_pg_sz	= SPACC_CRYPTO_IPSEC_HASH_PG_SZ;
		engine->fifo_sz		= SPACC_CRYPTO_IPSEC_FIFO_SZ;
		engine->algs		= ipsec_engine_algs;
		engine->num_algs	= ARRAY_SIZE(ipsec_engine_algs);
		engine->aeads		= ipsec_engine_aeads;
		engine->num_aeads	= ARRAY_SIZE(ipsec_engine_aeads);
	} else if (of_device_is_compatible(np, "picochip,spacc-l2")) {
		engine->max_ctxs	= SPACC_CRYPTO_L2_MAX_CTXS;
		engine->cipher_pg_sz	= SPACC_CRYPTO_L2_CIPHER_PG_SZ;
		engine->hash_pg_sz	= SPACC_CRYPTO_L2_HASH_PG_SZ;
		engine->fifo_sz		= SPACC_CRYPTO_L2_FIFO_SZ;
		engine->algs		= l2_engine_algs;
		engine->num_algs	= ARRAY_SIZE(l2_engine_algs);
	} else {
		return -EINVAL;
	}

	engine->name = dev_name(&pdev->dev);

	engine->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(engine->regs))
		return PTR_ERR(engine->regs);

	irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!irq) {
		dev_err(&pdev->dev, "no memory/irq resource for engine\n");
		return -ENXIO;
	}

	if (devm_request_irq(&pdev->dev, irq->start, spacc_spacc_irq, 0,
			     engine->name, engine)) {
		dev_err(engine->dev, "failed to request IRQ\n");
		return -EBUSY;
	}

	engine->dev		= &pdev->dev;
	engine->cipher_ctx_base = engine->regs + SPA_CIPH_KEY_BASE_REG_OFFSET;
	engine->hash_key_base	= engine->regs + SPA_HASH_KEY_BASE_REG_OFFSET;

	engine->req_pool = dmam_pool_create(engine->name, engine->dev,
		MAX_DDT_LEN * sizeof(struct spacc_ddt), 8, SZ_64K);
	if (!engine->req_pool)
		return -ENOMEM;

	spin_lock_init(&engine->hw_lock);

	engine->clk = clk_get(&pdev->dev, "ref");
	if (IS_ERR(engine->clk)) {
		dev_info(&pdev->dev, "clk unavailable\n");
		return PTR_ERR(engine->clk);
	}

	if (clk_prepare_enable(engine->clk)) {
		dev_info(&pdev->dev, "unable to prepare/enable clk\n");
		ret = -EIO;
		goto err_clk_put;
	}

	ret = device_create_file(&pdev->dev, &dev_attr_stat_irq_thresh);
	if (ret)
		goto err_clk_disable;


	/*
	 * Use an IRQ threshold of 50% as a default. This seems to be a
	 * reasonable trade off of latency against throughput but can be
	 * changed at runtime.
	 */
	engine->stat_irq_thresh = (engine->fifo_sz / 2);

	/*
	 * Configure the interrupts. We only use the STAT_CNT interrupt as we
	 * only submit a new packet for processing when we complete another in
	 * the queue. This minimizes time spent in the interrupt handler.
	 */
	writel(engine->stat_irq_thresh << SPA_IRQ_CTRL_STAT_CNT_OFFSET,
	       engine->regs + SPA_IRQ_CTRL_REG_OFFSET);
	writel(SPA_IRQ_EN_STAT_EN | SPA_IRQ_EN_GLBL_EN,
	       engine->regs + SPA_IRQ_EN_REG_OFFSET);

	timer_setup(&engine->packet_timeout, spacc_packet_timeout, 0);

	INIT_LIST_HEAD(&engine->pending);
	INIT_LIST_HEAD(&engine->completed);
	INIT_LIST_HEAD(&engine->in_progress);
	engine->in_flight = 0;
	tasklet_init(&engine->complete, spacc_spacc_complete,
		     (unsigned long)engine);

	platform_set_drvdata(pdev, engine);

	ret = -EINVAL;
	INIT_LIST_HEAD(&engine->registered_algs);
	for (i = 0; i < engine->num_algs; ++i) {
		engine->algs[i].engine = engine;
		err = crypto_register_alg(&engine->algs[i].alg);
		if (!err) {
			list_add_tail(&engine->algs[i].entry,
				      &engine->registered_algs);
			ret = 0;
		}
		if (err)
			dev_err(engine->dev, "failed to register alg \"%s\"\n",
				engine->algs[i].alg.cra_name);
		else
			dev_dbg(engine->dev, "registered alg \"%s\"\n",
				engine->algs[i].alg.cra_name);
	}

	INIT_LIST_HEAD(&engine->registered_aeads);
	for (i = 0; i < engine->num_aeads; ++i) {
		engine->aeads[i].engine = engine;
		err = crypto_register_aead(&engine->aeads[i].alg);
		if (!err) {
			list_add_tail(&engine->aeads[i].entry,
				      &engine->registered_aeads);
			ret = 0;
		}
		if (err)
			dev_err(engine->dev, "failed to register alg \"%s\"\n",
				engine->aeads[i].alg.base.cra_name);
		else
			dev_dbg(engine->dev, "registered alg \"%s\"\n",
				engine->aeads[i].alg.base.cra_name);
	}

	if (!ret)
		return 0;

	del_timer_sync(&engine->packet_timeout);
	device_remove_file(&pdev->dev, &dev_attr_stat_irq_thresh);
err_clk_disable:
	clk_disable_unprepare(engine->clk);
err_clk_put:
	clk_put(engine->clk);

	return ret;
}