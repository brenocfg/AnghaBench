__attribute__((used)) static __inline void
nlm_write_ucore_reg(int reg, unsigned int val)
{
	volatile unsigned int *addr = (volatile void *)reg;

	*addr = val;
}